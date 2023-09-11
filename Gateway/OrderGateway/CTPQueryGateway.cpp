//
// Created by Chuanchao Lyu on 2023/9/11.
//
#include "CTPQueryGateway.h"

namespace gateway{
    std::shared_ptr<CTPQueryGateway> CTPQueryGateway::CreateCTPQueryApi() {
        static auto pQuery = std::make_shared<CTPQueryGateway>();
        return pQuery;
    }

    CTPQueryGateway::CTPQueryGateway(){}
    CTPQueryGateway::~CTPQueryGateway() {}

    void CTPQueryGateway::init(const std::string &file) {
        _logger->info("CTPQueryGateway::Init");
        _tradeApi = CThostFtdcTraderApi::CreateFtdcTraderApi("logs/");
        _tradeApi->RegisterSpi(this);
        _tradeApi->SubscribePrivateTopic(THOST_TERT_QUICK);
        _tradeApi->SubscribePublicTopic(THOST_TERT_QUICK);
        GetUserInfo(file);
        Connect();
        //QueryInstruments();
    }

    std::vector<datafeed::FutureDefinition> CTPQueryGateway::QueryInstruments() {
        _logger->info("QueryInstruments ");
        if(!_futs.isfull())
        {
            CThostFtdcQryInstrumentField field;
            memset(&field, 0, sizeof(field));
            _tradeApi->ReqQryInstrument(&field, _status.requestID++);
            while(!_futs.isfull())
            {
                usleep(1000);
            }
            _logger->info("############################### CTPQueryGateway::QueryInstruments Finished ####################################");
        }
        return _futs.getData();
    }

    void CTPQueryGateway::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo,
                                             int nRequestID, bool bIsLast) {
        //_logger->info("OnRspQryInstrument");
        if(pInstrument != NULL)
        {
            datafeed::FutureDefinition fut;
            fut.set_instrumentid(pInstrument->InstrumentID);
            //fut.set_instrumentname(pInstrument->InstrumentName);
            fut.set_product(pInstrument->ProductID);
            int DeliveryYear = pInstrument->DeliveryYear;
            int DeliveryMonth = pInstrument->DeliveryMonth;
            fut.set_expiredate(pInstrument->ExpireDate);
            fut.set_pricetick(pInstrument->PriceTick);
            fut.set_exchangeid(pInstrument->ExchangeID);
            fut.set_multiplier(pInstrument->VolumeMultiple);
            switch(pInstrument->ProductClass)
            {
                case THOST_FTDC_PC_Futures :
                    _futs.push(fut);
                    break;
                default:
                    break;
            }
        }
        if(bIsLast)
            _futs.setfull();
    }

    std::vector<position::AccountPosition> CTPQueryGateway::QueryPosition() {
        _accpos.clear();
        CThostFtdcQryInvestorPositionField field;
        memset(&field, 0, sizeof(field));
        strcpy(field.BrokerID, _user.brokerID.c_str());
        strcpy(field.InvestorID, _user.userID.c_str());
        _tradeApi->ReqQryInvestorPosition(&field, _status.requestID++);
        while(!_accpos.isfull())
        {
            usleep(1000);
        }
        _logger->info("############################### CTPQueryGateway::QueryPosition Finished ####################################");
        return _accpos.getData();
    }

    void CTPQueryGateway::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition,
                                                   CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        _logger->info("CTPQueryGateway::OnRspQryInvestorPosition");
        if(pInvestorPosition != NULL)
        {
            position::AccountPosition pos;
            _logger->info("OnRspQryInvestorPosition {} PosiDirection: {},Position{}, TodayPosition {}, isLast: {}", pInvestorPosition->InstrumentID,
                          pInvestorPosition->PosiDirection, pInvestorPosition->Position, pInvestorPosition->TodayPosition, bIsLast);
            //auto product = _conManger->GetContractSymbol(pInvestorPosition->InstrumentID);
            std::string product;
            if(product.size()>0){
                pos.set_instrumentid(pInvestorPosition->InstrumentID);
                pos.set_totalvolume(pInvestorPosition->Position);
                pos.set_todayvolume(pInvestorPosition->TodayPosition);
                //pos.set_productid(product);
                if(pInvestorPosition->PosiDirection == THOST_FTDC_PD_Long){
                    pos.set_direction(position::POS_LONG);
                }else if(pInvestorPosition->PosiDirection == THOST_FTDC_PD_Short){
                    pos.set_direction(position::POS_SHORT);
                } else
                {
                    _logger->info("WHAT HAPPENED: OnRspQryInvestorPosition PosiDirection {}", pInvestorPosition->PosiDirection);
                    pos.set_direction(position::POS_BUTT);
                }
                _accpos.push(pos);
            }
        }
        if(bIsLast)
        {
            _accpos.setfull();
        }

    }

    void CTPQueryGateway::QueryOrder() {

    }

    void CTPQueryGateway::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                                        bool bIsLast) {

    }




    void CTPQueryGateway::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
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

#include "CTPQueryGateway.h"
