//
// Created by Chuanchao Lyu on 2023/8/28.
//

#ifndef ORDERTEST_CTPORDERGATEWAY_H
#define ORDERTEST_CTPORDERGATEWAY_H

#include "tradeSpi.h"
#include "OrderGatewaylistener.h"
#include "order.pb.h"

namespace gateway{
    class CTPOrderGateway:public CTPTradeSpi{
    public:
        static std::shared_ptr<CTPOrderGateway> CreateCTPTradeApi();
        CTPOrderGateway();
        ~CTPOrderGateway() override;
        void init(const std::string&);
        void RegisterListener(std::shared_ptr<OrderGatewayListener>);

        int CancelOrder(std::shared_ptr<Orders::CancelOrder>);
        int SubmitOrder(std::shared_ptr<Orders::SubmitOrder>);
    private:

        //void FillErrorInfo(std::shared_ptr<ctp_spi::RspError>&, CThostFtdcRspInfoField *,int,bool);
        //std::string OrderStatustoString(TThostFtdcOrderStatusType);
        //std::string SubmitStatustoString(TThostFtdcOrderSubmitStatusType);
        //Simorder::OmsOrderStatus GetOrderStatusFromRtn(TThostFtdcOrderStatusType);
        //Simorder::OrderDirection GetOrderDirectionFromRtnOrder(TThostFtdcDirectionType,TThostFtdcCombOffsetFlagType);
        void FillOrderDirection(CThostFtdcInputOrderField &order, Orders::OrderDirection orderDirection);
    private:
        //virtual void OnHeartBeatWarning(int nTimeLapse) override;
        void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

        //error of submitorder
        void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
        void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) override ;
        //error of cancelorder
        void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
        void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo) override;

        void OnRtnOrder(CThostFtdcOrderField *pOrder) override ;
        void OnRtnTrade(CThostFtdcTradeField *pTrade) override ;


    private:

        std::mutex _listenmtx;
        std::shared_ptr<OrderGatewayListener> _listener;
    };
}



#endif //ORDERTEST_CTPORDERGATEWAY_H
