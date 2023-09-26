//
// Created by ChuanchaoLyu on 2023/9/10.
//

#include "tradeSpi.h"
#include "config.h"

using namespace std;
namespace gateway{

    CTPTradeSpi::CTPTradeSpi():_tradeApi{nullptr} {}

    CTPTradeSpi::~CTPTradeSpi() {
        Shutdown();
    }


    void CTPTradeSpi::GetUserInfo(const std::string & file) {
        Config config(file);
        _user.ip = config.pString("tdip");
        _user.port = config.pInt("tdport");
        _user.brokerID = config.pString("tdbrokerid");
        _user.userID = config.pString("tduserid");
        _user.password = config.pString("tdpassword");
        _user.appid = config.pString("appid");
        _user.authcode = config.pString("authcode");
        //_logger->info("{}; {} ;{}",_user.ip,_user.brokerID,_user.port);
    }

    void CTPTradeSpi::Connect() {

        _logger->info("Call CTPTradeSpi::Connect");
        string ipAddress = "tcp://" + _user.ip + ":" + std::to_string(_user.port);
        _logger->info("ipAddress {}",ipAddress);
        _tradeApi->RegisterFront(const_cast<char*>(ipAddress.c_str()));
        _tradeApi->Init();

        unique_lock<mutex> frontlk(_front.mtx);
        if(_front.cv.wait_for(frontlk,chrono::seconds(3))==cv_status::timeout){
            _logger->error("CTPTradeSpi::Connect, front connected timeout!");
            return;
        }


        UserAuthenticate();
        unique_lock<mutex> authlk(_auth.mtx);
        if(_auth.cv.wait_for(authlk,chrono::seconds(3))==cv_status::timeout){
            _logger->error("CTPTradeSpi::Connect,User Authenticate timeout!");
            return;
        }

        UserLogin();
        unique_lock<mutex> loginlk(_login.mtx);
        if(_login.cv.wait_for(loginlk,chrono::seconds(3))==cv_status::timeout){
            _logger->error("CTPTradeSpi::Connect,User Login timeout!");
            return;
        }
        ConfirmSettlementInfo();
        this_thread::sleep_for(std::chrono::seconds(2));
    }

    void CTPTradeSpi::OnFrontConnected() {
        _logger->info("OnFrontConnected!");
        lock_guard<mutex> frontlk(_front.mtx);
        _front.status = true;
        _logger->info("OnFrontConnected finish!");
        _front.cv.notify_all();
    }

    void CTPTradeSpi::OnFrontDisconnected(int nReason)
    {
        _status.isConnected = false;
        _front.status = false;
        _logger->info("OnFrontDisconnected reason: {}", nReason);
    }


    void CTPTradeSpi::UserAuthenticate() {
        _logger->info("pReqUserAuthenticate");
        CThostFtdcReqAuthenticateField pReqUserAuthField;
        memset(&pReqUserAuthField, 0, sizeof(pReqUserAuthField));
        memcpy(&pReqUserAuthField.BrokerID, _user.brokerID.c_str(), _user.brokerID.length());
        memcpy(&pReqUserAuthField.UserID, _user.userID.c_str(), _user.userID.length());
        memcpy(&pReqUserAuthField.AppID, _user.appid.c_str(), _user.appid.length());
        memcpy(&pReqUserAuthField.AuthCode, _user.authcode.c_str(), _user.authcode.length());
        _logger->info("Authenticate with brokerid {} userid {}  appid={} authcode={}",
                      pReqUserAuthField.BrokerID, pReqUserAuthField.UserID, pReqUserAuthField.AppID,
                      pReqUserAuthField.AuthCode);
        _tradeApi->ReqAuthenticate(&pReqUserAuthField, ++_status.requestID);
    }

    void CTPTradeSpi::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField,
                                            CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {

        TThostFtdcErrorIDType	ErrorID;
        TThostFtdcErrorMsgType	ErrorMsg;

        if(pRspInfo->ErrorID != 0)
        {
            _logger->info("OnRspAuthenticate errorID: {}  {}", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
            _auth.status = false;
        }else {
            _logger->info("User Authenticate finished!");
            lock_guard<mutex> authlk(_auth.mtx);
            _auth.status = true;
            _auth.cv.notify_all();
        }
    }

    void CTPTradeSpi::UserLogin() {
        _logger->info("pReqUserLoginField");
        CThostFtdcReqUserLoginField pReqUserLoginField;
        memset(&pReqUserLoginField,0,sizeof(pReqUserLoginField));
        memcpy(&pReqUserLoginField.BrokerID,_user.brokerID.c_str(),_user.brokerID.length());
        memcpy(&pReqUserLoginField.UserID, _user.userID.c_str(), _user.userID.length());
        memcpy(&pReqUserLoginField.Password, _user.password.c_str(), _user.password.length());
        _logger->info("Logging in with brokerid {} userid {}  userproductInfo{}",
                      pReqUserLoginField.BrokerID, pReqUserLoginField.UserID, pReqUserLoginField.UserProductInfo);

        //TThostFtdcClientSystemInfoType sysinfo = "MACOS";
        _tradeApi->ReqUserLogin(&pReqUserLoginField,++_status.requestID);
    }

    void CTPTradeSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo,
                                         int nRequestID, bool bIsLast) {
        TThostFtdcErrorIDType	ErrorID;
        TThostFtdcErrorMsgType	ErrorMsg;
        if(pRspInfo->ErrorID != 0)
        {
            _logger->info("OnRspUserLogin errorID: {}  {}", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
            _login.status = false;
        }else {
            _logger->info("User login finished!");
            lock_guard<mutex> loginlk(_login.mtx);
            _status.frontID = pRspUserLogin->FrontID;
            _status.SessionID = pRspUserLogin->SessionID;
            _status.maxorderref = atoi(pRspUserLogin->MaxOrderRef);
            _logger->info("maxorderref = {}",pRspUserLogin->MaxOrderRef);
            _login.status = true;
            _login.cv.notify_all();
        }
    }

    void CTPTradeSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout,
                                          CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
    {
        lock_guard<mutex> lk(_logout.mtx);
        _login.status = false;
        _status.isConnected = false;
        _logout.cv.notify_all();
    }

    void CTPTradeSpi::ConfirmSettlementInfo() {
        CThostFtdcSettlementInfoConfirmField field;
        std::memset(&field, 0, sizeof(field));
        std::memcpy(&field.BrokerID, _user.brokerID.c_str(), _user.brokerID.length());
        std::memcpy(&field.InvestorID, _user.userID.c_str(), _user.userID.length());
        time_t t = time(0);
        struct tm * now = std::localtime( & t );
        std::string date = std::to_string((now->tm_year+1900)*10000 + (now->tm_mon + 1) * 100 + now->tm_mday);
        char time[32];
        std::strftime(time, sizeof(time), "%H:%M:%S", now);
        std::memcpy(&field.ConfirmDate, date.c_str(), date.length());
        std::memcpy(&field.ConfirmTime, time, 8);

        //_logger->info("date {} time{} ", date, time);
        _tradeApi->ReqSettlementInfoConfirm(&field, ++_status.requestID);
    }

    void CTPTradeSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm,
                                                     CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        if(pRspInfo->ErrorID != 0){
            _logger->info(" OnRspSettlementInfoConfirm errorID: {}  {}", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
        }else{
            _logger->info(" SettlementInfoConfirm Finished!");
            _status.isConnected = true;
        }
    }



    void CTPTradeSpi::Shutdown() {
        if(_tradeApi){
            _logger->info("Shutdown CTPTradeSpi");
            _tradeApi->RegisterSpi(nullptr);
            _tradeApi->Release();
            _tradeApi = nullptr;
            _logger->info("CTPTradeSpi Closed!");
        }
    }

    std::string CTPTradeSpi::GetTradingDate() {
        return _tradeApi->GetTradingDay();
    }
}
