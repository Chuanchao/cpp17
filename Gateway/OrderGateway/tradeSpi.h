//
// Created by ChuanchaoLyu on 2023/9/10.
//

#ifndef ORDERTEST_TRADESPI_H
#define ORDERTEST_TRADESPI_H

#include <string>
#include <memory>
#include <unordered_map>
#include "ThostFtdcTraderApi.h"

#include "LogWrapper.h"
#include "ctpData.h"

namespace gateway{
    class CTPTradeSpi:public CThostFtdcTraderSpi, protected LoggerBase{
    public:
        CTPTradeSpi();
        virtual ~CTPTradeSpi();
        void GetUserInfo(const std::string&);
        int64_t getCTPmaxorderref() const{return _status.maxorderref;}
        int getCTPSessionID() const {return _status.SessionID;}
        int getCTPfrontID() const {return _status.frontID;}
        std::string GetTradingDate();
        void Shutdown();
    protected:
        void Connect();
        void UserAuthenticate();
        void UserLogin();
        //void UserLogout();
        void ConfirmSettlementInfo();
        bool isActive() const{return _status.isConnected;}
    protected:
        void OnFrontConnected() override;
        void OnFrontDisconnected(int nReason) override;
        //virtual void OnHeartBeatWarning(int nTimeLapse) override;
        void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField,
                                       CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
        void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
                                    CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
        void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout,
                                     CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
        void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm,
                                                CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;


    protected:
        CThostFtdcTraderApi* _tradeApi;
        //User Info
        UserInfo _user;

        //api status
        ctpStatus _status;
        Monitor _front;
        Monitor _auth;
        Monitor _login;
        Monitor _logout;
    };
}



#endif //ORDERTEST_TRADESPI_H
