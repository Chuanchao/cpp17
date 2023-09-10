//
// Created by Chuanchao Lyu on 2023/9/8.
//

#include "CTPFeedGateway.h"
#include "config.h"
using namespace gateway;

std::shared_ptr<CTPFeedGateway> CTPFeedGateway::CreateCTPFeedApi() {
    static auto pFeed = make_shared<CTPFeedGateway>();
    return pFeed;
}

CTPFeedGateway::CTPFeedGateway():_mdApi{nullptr},_consumer{nullptr} {}
CTPFeedGateway::~CTPFeedGateway() {
    shutdown();
}

void CTPFeedGateway::shutdown() {
    _logger->info("CTPFeedGateway::shutdown");
    if(_mdApi){
        _mdApi->RegisterSpi(nullptr);
        _mdApi->Release();
        _mdApi = nullptr;
    }
}

void CTPFeedGateway::RegisterConsumer(std::shared_ptr<FeedConsumer> cs) {
    std::lock_guard<std::mutex> lk{_conmtx};
    _consumer = cs;
}

std::string CTPFeedGateway::GetTradingDay() {
    return _mdApi->GetTradingDay();
}

void CTPFeedGateway::init(const std::string& file) {
    _logger->info("CTPFeedGateway::init");
    _mdApi = CThostFtdcMdApi::CreateFtdcMdApi("logs/");
    _mdApi->RegisterSpi(this);

    Config config(file);
    _user.ip = config.pString("mdip");
    _user.port = config.pInt("mdport");
    _user.brokerID = config.pString("mdbrokerid");
    _user.userID = config.pString("mduserid");
    _user.password = config.pString("mdpassword");
    //_logger->info("{}; {} ;{}",_user.ip,_user.brokerID,_user.port);
    connect();
}

void CTPFeedGateway::connect() {
    _logger->info("Call FeedOrderGateway::Connect");
    string ipAddress = "tcp://" + _user.ip + ":" + std::to_string(_user.port);
    _logger->info("ipAddress {}",ipAddress);
    _mdApi->RegisterFront(const_cast<char*>(ipAddress.c_str()));
    _mdApi->Init();

    unique_lock<mutex> frontlk(_front.mtx);
    if(_front.cv.wait_for(frontlk,chrono::seconds(3))==cv_status::timeout){
        _logger->error("FeedOrderGateway::Connect, front connected timeout!");
        return;
    }

    UserLogin();
    unique_lock<mutex> loginlk(_login.mtx);
    if(_login.cv.wait_for(loginlk,chrono::seconds(3))==cv_status::timeout){
        _logger->error("CTPOrderGateway::Connect,User Login timeout!");
        return;
    }
}

void CTPFeedGateway::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
    datafeed::TickData tick;
    tick.set_contract(pDepthMarketData->InstrumentID);
    tick.set_exchangeid(pDepthMarketData->ExchangeID);
    tick.mutable_bid1()->set_price(pDepthMarketData->BidPrice1);
    tick.mutable_bid1()->set_quantity(pDepthMarketData->BidVolume1);
    tick.mutable_bid2()->set_price(pDepthMarketData->BidPrice2);
    tick.mutable_bid2()->set_quantity(pDepthMarketData->BidVolume2);
    tick.mutable_bid3()->set_price(pDepthMarketData->BidPrice3);
    tick.mutable_bid3()->set_quantity(pDepthMarketData->BidVolume3);
    tick.mutable_bid4()->set_price(pDepthMarketData->BidPrice4);
    tick.mutable_bid4()->set_quantity(pDepthMarketData->BidVolume4);
    tick.mutable_bid5()->set_price(pDepthMarketData->BidPrice5);
    tick.mutable_bid5()->set_quantity(pDepthMarketData->BidVolume5);
    tick.mutable_ask1()->set_price(pDepthMarketData->AskPrice1);
    tick.mutable_ask1()->set_quantity(pDepthMarketData->AskVolume1);
    tick.mutable_ask2()->set_price(pDepthMarketData->AskPrice2);
    tick.mutable_ask2()->set_quantity(pDepthMarketData->AskVolume2);
    tick.mutable_ask3()->set_price(pDepthMarketData->AskPrice3);
    tick.mutable_ask3()->set_quantity(pDepthMarketData->AskVolume3);
    tick.mutable_ask4()->set_price(pDepthMarketData->AskPrice4);
    tick.mutable_ask4()->set_quantity(pDepthMarketData->AskVolume4);
    tick.mutable_ask5()->set_price(pDepthMarketData->AskPrice5);
    tick.mutable_ask5()->set_quantity(pDepthMarketData->AskVolume5);
    tick.set_lasttradeprice(pDepthMarketData->LastPrice);
    tick.set_open(pDepthMarketData->OpenPrice);
    tick.set_highest(pDepthMarketData->HighestPrice);
    tick.set_lowest(pDepthMarketData->LowestPrice);
    tick.set_openinterest(pDepthMarketData->OpenInterest);
    tick.set_volume(pDepthMarketData->Volume);
    tick.set_turnover(pDepthMarketData->Turnover);
    tick.set_averageprice(pDepthMarketData->AveragePrice);
    tick.set_tradingdate(pDepthMarketData->TradingDay);
    tick.set_exchangetime(pDepthMarketData->UpdateTime);
    tick.set_upperlimitprice(pDepthMarketData->UpperLimitPrice);
    tick.set_lowlimitprice(pDepthMarketData->LowerLimitPrice);
    tick.set_presettlement(pDepthMarketData->PreSettlementPrice);
    tick.set_tradingdate(GetTradingDay());
    if(_consumer) {
        _consumer->ProcessTickData(tick);
    } else{
        _logger->error("FeedGateway::consumer not registered!");
    }
}


void CTPFeedGateway::OnFrontConnected() {
    _logger->info("FeedGateway::OnFrontConnected");
    lock_guard<mutex> lock(_front.mtx);
    _front.status = true;
    _front.cv.notify_one();
    _logger->info("OnFrontConnected Finished!");
}

void CTPFeedGateway::OnFrontDisconnected(int nReason) {
    std::lock_guard<std::mutex> lock(_front.mtx);
    _front.status = false;
    _front.cv.notify_one();
    _logger->info("OnFrontDisconnected reason: {}", nReason);
}


void CTPFeedGateway::UserLogin() {
    _logger->info("pReqUserLoginField");
    CThostFtdcReqUserLoginField pReqUserLoginField;
    memset(&pReqUserLoginField,0,sizeof(pReqUserLoginField));
    memcpy(&pReqUserLoginField.BrokerID,_user.brokerID.c_str(),_user.brokerID.length());
    memcpy(&pReqUserLoginField.UserID, _user.userID.c_str(), _user.userID.length());
    memcpy(&pReqUserLoginField.Password, _user.password.c_str(), _user.password.length());
    _logger->info("Logging in with brokerid {} userid {}  userproductInfo{}",
                      pReqUserLoginField.BrokerID, pReqUserLoginField.UserID, pReqUserLoginField.UserProductInfo);

    //TThostFtdcClientSystemInfoType sysinfo = "MACOS";
    _mdApi->ReqUserLogin(&pReqUserLoginField,++_status.requestID);
}

void CTPFeedGateway::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo,
                                    int nRequestID, bool bIsLast) {
    TThostFtdcErrorIDType	ErrorID;
    TThostFtdcErrorMsgType	ErrorMsg;
    std::lock_guard<std::mutex> lock(_login.mtx);
    if(pRspInfo->ErrorID != 0)
    {
        _logger->info("OnRspUserLogin errorID: {} {}", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
        _login.status = false;
    }else
    {
        _login.status = true;
        _logger->info("TradingDay = {}",GetTradingDay());
        _login.cv.notify_one();
    }
}

void CTPFeedGateway::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
}

void CTPFeedGateway::SubScribe(const std::vector<std::string> & symbols) {
    _logger->info("CTPFeedGateway::SubScribe instruments");
    if(_login.status){
        char* contracts[symbols.size()];
        for (size_t i = 0;i<symbols.size();i++){
            contracts[i]=new char[symbols[i].length()+1];
            memcpy(contracts[i],symbols[i].c_str(),symbols[i].length()+1);
            //_logger->info("Subscribint to {}",contracts[i]);
        }
        _mdApi->SubscribeMarketData(contracts,symbols.size());

        for(size_t j=0;j<symbols.size();j++){
            delete [] contracts[j];
        }
    }
}

void CTPFeedGateway::UnsubScribe(const std::vector<std::string> & symbols) {
    _logger->info("CTPFeedGateway::UnSubScribe instruments");
    if(_login.status){
        char* contracts[symbols.size()];
        for (size_t i = 0;i<symbols.size();i++){
            contracts[i]=new char[symbols[i].length()+1];
            memcpy(contracts[i],symbols[i].c_str(),symbols[i].length()+1);
            //_logger->info("UnSubscribint to {}",contracts[i]);
        }
        _mdApi->UnSubscribeMarketData(contracts,symbols.size());

        for(size_t j=0;j<symbols.size();j++){
            delete [] contracts[j];
        }
    }
}




void CTPFeedGateway::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                                        CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {


    if(pRspInfo and pRspInfo->ErrorID != 0)
    {
        _logger->info("OnRspSubMarketData errorID: {}  {}", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
    } else{
        //if(pSpecificInstrument) _logger->info("OnRspSubMarketData {}  islast:{}", pSpecificInstrument->InstrumentID , bIsLast);
    }
}

void CTPFeedGateway::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                                          CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {

    //_logger->info("FeedGateway::Unsubscribe instrumentID {}",pSpecificInstrument->InstrumentID);
}




