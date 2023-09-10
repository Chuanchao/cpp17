//
// Created by Chuanchao Lyu on 2023/8/28.
//

#ifndef ORDERTEST_CTPORDERGATEWAY_H
#define ORDERTEST_CTPORDERGATEWAY_H

#include "tradeSpi.h"
#include "OrderGatewaylistener.h"

namespace gateway{
    class CTPOrderGateway:public CTPTradeSpi{
    public:
        static std::shared_ptr<CTPOrderGateway> CreateCTPTradeApi();
        CTPOrderGateway();
        ~CTPOrderGateway() override;
        void init(const std::string&);
        void RegisterListener(std::shared_ptr<OrderGatewayListener>);

        //int CancelOrder(shared_ptr<Simorder::RequestCancelOrder>);
        //int SubmitOrder(shared_ptr<Simorder::RequestSubmitOrder>,int64_t);
    private:

        //void FillErrorInfo(std::shared_ptr<ctp_spi::RspError>&, CThostFtdcRspInfoField *,int,bool);
        //std::string OrderStatustoString(TThostFtdcOrderStatusType);
        //std::string SubmitStatustoString(TThostFtdcOrderSubmitStatusType);
        //Simorder::OmsOrderStatus GetOrderStatusFromRtn(TThostFtdcOrderStatusType);
        //Simorder::OrderDirection GetOrderDirectionFromRtnOrder(TThostFtdcDirectionType,TThostFtdcCombOffsetFlagType);
        //void FillOrderDirection(CThostFtdcInputOrderField &order, Simorder::OrderDirection orderDirection);
    private:
        //virtual void OnHeartBeatWarning(int nTimeLapse) override;
        void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

        /***
        //Order callback
        virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder,
                                      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;


        virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) override ;
        virtual void OnRtnOrder(CThostFtdcOrderField *pOrder) override ;
        virtual void OnRtnTrade(CThostFtdcTradeField *pTrade) override ;
        //Error callback
        ***/

    private:

        std::mutex _listenmtx;
        std::shared_ptr<OrderGatewayListener> _listener;
    };
}



#endif //ORDERTEST_CTPORDERGATEWAY_H
