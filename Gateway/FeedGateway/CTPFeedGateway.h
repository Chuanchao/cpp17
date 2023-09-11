//
// Created by Chuanchao Lyu on 2023/9/8.
//

#ifndef ORDERTEST_CTPFEEDGATEWAY_H
#define ORDERTEST_CTPFEEDGATEWAY_H

#include "ctpData.h"
#include "LogWrapper.h"
#include "ThostFtdcMdApi.h"
#include "FeedConsumer.h"

namespace gateway {
    class CTPFeedGateway : public CThostFtdcMdSpi, private LoggerBase {
    public:
        static std::shared_ptr<CTPFeedGateway> CreateCTPFeedApi();
        CTPFeedGateway();
        virtual ~CTPFeedGateway();
        void init(const std::string&);
        void RegisterConsumer(std::shared_ptr<FeedConsumer>);
        bool isActive() const { return _login.status; };

        void SubScribe(const std::vector<std::string> &);
        void UnsubScribe(const std::vector<std::string> &);
        std::string GetTradingDay();
        void shutdown();
    private:
        void connect();
        void UserLogin();
        virtual void OnFrontConnected() override ;
        virtual void OnFrontDisconnected(int nReason) override ;
        //virtual void OnHeartBeatWarning(int nTimeLapse) override ;
        virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override ;
        //virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override ;
        virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override ;
        virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override ;
        virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override ;
        virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);
    private:
        CThostFtdcMdApi* _mdApi;
        std::mutex _conmtx;
        std::shared_ptr<FeedConsumer> _consumer;
        //User Info
        UserInfo _user;

        //api status
        ctpStatus _status;
        Monitor _front;
        Monitor _login;
        //Monitor _logout;
    };

}


#endif //ORDERTEST_CTPFEEDGATEWAY_H
