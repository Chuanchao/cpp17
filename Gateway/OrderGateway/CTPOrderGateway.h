//
// Created by Chuanchao Lyu on 2023/8/28.
//

#ifndef ORDERTEST_CTPORDERGATEWAY_H
#define ORDERTEST_CTPORDERGATEWAY_H
#include <string>
#include <atomic>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <unordered_map>
#include "ThostFtdcTraderApi.h"

#include "LogWrapper.h"
#include "ctpData.h"
#include "OrderGatewaylistener.h"

namespace gateway{
    class CTPOrderGateway:public CThostFtdcTraderSpi,private LoggerBase{
    public:
        static std::shared_ptr<CTPOrderGateway> CreateCTPTradeApi();
        CTPOrderGateway();
        ~CTPOrderGateway();
        void init(const std::string&);
        void RegisterListener(std::shared_ptr<OrderGatewayListener>);
        int64_t getCTPmaxorderref() const{return _status.maxorderref;}
        int getCTPSessionID() const {return _status.SessionID;}
        int getCTPfrontID() const {return _status.frontID;}
        //Query functions
        //InstrumentIDs
        //void QueryAllPosition();
        //void QueryPosition(const std::string&);
        //void QueryTradingAccount();

        //int CancelOrder(shared_ptr<Simorder::RequestCancelOrder>);
        //int SubmitOrder(shared_ptr<Simorder::RequestSubmitOrder>,int64_t);
        std::string GetTradingDate();
        void Shutdown();
    private:
        void Connect();

        void UserAuthenticate();
        void UserLogin();

        //void UserLogout();
        void ConfirmSettlementInfo();
        //void FillErrorInfo(std::shared_ptr<ctp_spi::RspError>&, CThostFtdcRspInfoField *,int,bool);
        //std::string OrderStatustoString(TThostFtdcOrderStatusType);
        //std::string SubmitStatustoString(TThostFtdcOrderSubmitStatusType);
        //Simorder::OmsOrderStatus GetOrderStatusFromRtn(TThostFtdcOrderStatusType);
        //Simorder::OrderDirection GetOrderDirectionFromRtnOrder(TThostFtdcDirectionType,TThostFtdcCombOffsetFlagType);
        //void FillOrderDirection(CThostFtdcInputOrderField &order, Simorder::OrderDirection orderDirection);
        bool isActive() const{return _status.isConnected;}
    private:
        virtual void OnFrontConnected() override;
        virtual void OnFrontDisconnected(int nReason) override;
        //virtual void OnHeartBeatWarning(int nTimeLapse) override;
        virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField,
                                       CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
        virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
                                    CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
        virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout,
                                     CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
        /***
        //Query Callback
        virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition,
                                              CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
        virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount,
                                            CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;



        //Order callback
        virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder,
                                      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;


        virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) override ;
        virtual void OnRtnOrder(CThostFtdcOrderField *pOrder) override ;
        virtual void OnRtnTrade(CThostFtdcTradeField *pTrade) override ;
        //Error callback
        ***/
        virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
        virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm,
                                                CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;


    private:

        CThostFtdcTraderApi* _tradeApi;
        std::mutex _listenmtx;
        std::shared_ptr<OrderGatewayListener> _listener;
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



#endif //ORDERTEST_CTPORDERGATEWAY_H
