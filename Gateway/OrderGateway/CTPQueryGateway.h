//
// Created by Chuanchao Lyu on 2023/9/11.
//

#ifndef ORDERTEST_CTPQUERYGATEWAY_H
#define ORDERTEST_CTPQUERYGATEWAY_H

#include "tradeSpi.h"
#include "datafeed.pb.h"
#include "position.pb.h"
#include <optional>


namespace gateway{
    class CTPQueryGateway:public CTPTradeSpi{
    public:
        static std::shared_ptr<CTPQueryGateway> CreateCTPQueryApi();
        CTPQueryGateway();
        ~CTPQueryGateway() override;
        void init(const std::string&);
        std::unordered_map<std::string,datafeed::FutureDefinition> QueryInstruments();
        std::unordered_map<std::string,position::AccountPosition> QueryPosition();
        void QueryOrder();
        std::optional<std::string> getProductID(const std::string&);
    private:
        void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo,
                           int nRequestID, bool bIsLast) override ;
        void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument,
                                CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
        void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition,
                                      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
        void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
    private:
        synQuery<datafeed::FutureDefinition> _futs;
        synQuery<position::AccountPosition> _accpos;
    };
}


#endif //ORDERTEST_CTPQUERYGATEWAY_H
