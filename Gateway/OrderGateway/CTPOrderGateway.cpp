//
// Created by Chuanchao Lyu on 2023/8/28.
//

#include "CTPOrderGateway.h"
#include "config.h"
using namespace std;
namespace gateway{
    std::shared_ptr<CTPOrderGateway> CTPOrderGateway::CreateCTPTradeApi() {
        static auto pTrade = make_shared<CTPOrderGateway>();
        return pTrade;
    }

    CTPOrderGateway::CTPOrderGateway():_listener{nullptr} {}

    CTPOrderGateway::~CTPOrderGateway() {}

    void CTPOrderGateway::RegisterListener(std::shared_ptr<OrderGatewayListener> listener) {
        _logger->info("CTPOrderGateway::RegisterListener");
        lock_guard<mutex> lk(_listenmtx);
        _listener = listener;
    }

    void CTPOrderGateway::init(const std::string &file) {
        _logger->info("CTPOrderGateway::Init");
        _tradeApi = CThostFtdcTraderApi::CreateFtdcTraderApi("logs/");
        _tradeApi->RegisterSpi(this);
        _tradeApi->SubscribePrivateTopic(THOST_TERT_RESTART);
        _tradeApi->SubscribePublicTopic(THOST_TERT_RESTART);
        GetUserInfo(file);
        Connect();
    }
    void CTPOrderGateway::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        if(pRspInfo->ErrorID != 0)
        {
            _logger->error("OnRspError ErrorID: {}. ErrorMsg: {}", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
            //auto message = make_shared<ctp_spi::RspError>();
            //FillErrorInfo(message,pRspInfo,nRequestID,bIsLast);
            //if(_listener) {
            //    _listener->OnError(message);
            //} else{
            //    _logger->error("Listener not register!");
            //}
        }
    }
}
