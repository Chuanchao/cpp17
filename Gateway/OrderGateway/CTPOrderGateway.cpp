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

    int CTPOrderGateway::SubmitOrder(std::shared_ptr<Orders::SubmitOrder> orderinfo) {
        CThostFtdcInputOrderField order;
        memset(&order, 0, sizeof(order));
        strcpy(order.BrokerID, _user.brokerID.c_str());
        strcpy(order.InvestorID, _user.userID.c_str());
        strcpy(order.InstrumentID, orderinfo->instid().c_str());
        strcpy(order.OrderRef, std::to_string(orderinfo->orderref()).c_str());
        //strcpy(order.UserID, _user.userID.c_str());
        FillOrderDirection(order,orderinfo->real_d());
        string productid = orderinfo->symbol();
        if (productid == "IH" or productid == "IF" or productid == "IC" ){
            order.CombHedgeFlag[0] = THOST_FTDC_HF_Hedge;
        } else{
            order.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
        }
        order.VolumeTotalOriginal = abs(orderinfo->amount());
        order.VolumeCondition = THOST_FTDC_VC_AV;
        order.ContingentCondition = THOST_FTDC_CC_Immediately;
        order.MinVolume = 1;
        order.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
        order.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
        order.LimitPrice = orderinfo->price();
        if(orderinfo->order_t() == Orders::GFD_ORDER){
            order.TimeCondition = THOST_FTDC_TC_GFD;
        }else{
            order.TimeCondition = THOST_FTDC_TC_IOC;
        }
        order.RequestID = ++_status.requestID;
        std::cout << "CTPOrderGateway::SubmitOrder BrokerID " << order.BrokerID
                  << " InvestorID: " << order.InvestorID
                  << " InstrumentID: " << order.InstrumentID << " Direction: " << order.Direction
                  << " TimeCondition: " << order.TimeCondition << " CombOffsetFlag: " << order.CombOffsetFlag
                  << " VolumeTotalOriginal: " << order.VolumeTotalOriginal << " LimitPrice: " << order.LimitPrice
                  << " OrderRef: " << order.OrderRef << " OrderPriceType: " << order.OrderPriceType
                  << " CombHedgeFlag: " << order.CombHedgeFlag
                  << " VolumeCondition: " << order.VolumeCondition
                  << " ContingentCondition: " << order.ContingentCondition
                  << " ForceCloseReason: " << order.ForceCloseReason
                  << std::endl;
        int k = _tradeApi->ReqOrderInsert(&order, order.RequestID);
        return k;

    }

    int CTPOrderGateway::CancelOrder(std::shared_ptr<Orders::CancelOrder> cancelinfo) {
        CThostFtdcInputOrderActionField cancelOrder;
        memset(&cancelOrder,0,sizeof(cancelOrder));
        strcpy(cancelOrder.BrokerID,_user.brokerID.c_str());
        strcpy(cancelOrder.InvestorID,_user.userID.c_str());
        strcpy(cancelOrder.UserID,_user.userID.c_str());
        strcpy(cancelOrder.OrderRef,std::to_string(cancelinfo->orderref()).c_str());

        cancelOrder.RequestID = ++_status.requestID;
        cancelOrder.FrontID = _status.frontID;
        cancelOrder.SessionID = _status.SessionID;
        cancelOrder.ActionFlag = THOST_FTDC_AF_Delete;
        int k = _tradeApi->ReqOrderAction(&cancelOrder,cancelOrder.RequestID);
        return k;
    }


    void CTPOrderGateway::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        if(pRspInfo->ErrorID != 0)
        {
            _logger->error("OnRspError ErrorID: {}. ErrorMsg: {}", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
            //auto message = make_shared<ctp_spi::RspError>();
            //FillErrorInfo(message,pRspInfo,nRequestID,bIsLast);
            //lock_guard<mutex> lk(_listenmtx);
            //if(_listener) {
            //    _listener->OnError(message);
            //} else{
            //    _logger->error("Listener not register!");
            //}
        }
    }

    void CTPOrderGateway::FillOrderDirection(CThostFtdcInputOrderField &order, Orders::OrderDirection orderDirection) {
        switch(orderDirection){
            case Orders::OPEN_LONG:
                order.Direction = THOST_FTDC_D_Buy; //THOST_FTDC_D_Buy : THOST_FTDC_D_Sell;
                order.CombOffsetFlag[0] = THOST_FTDC_OF_Open; // 0.open 1.close 3.closetoday
                break;
            case Orders::OPEN_SHORT:
                order.Direction = THOST_FTDC_D_Sell; //THOST_FTDC_D_Buy : THOST_FTDC_D_Sell;
                order.CombOffsetFlag[0] = THOST_FTDC_OF_Open; // 0.open 1.close 3.closetoday
                break;
            case Orders::CLOSE_LONG:
                order.Direction = THOST_FTDC_D_Sell; //THOST_FTDC_D_Buy : THOST_FTDC_D_Sell;
                order.CombOffsetFlag[0] = THOST_FTDC_OF_Close; // 0.open 1.close 3.closetoday
                break;
            case Orders::CLOSE_SHORT:
                order.Direction = THOST_FTDC_D_Buy; //THOST_FTDC_D_Buy : THOST_FTDC_D_Sell;
                order.CombOffsetFlag[0] = THOST_FTDC_OF_Close; // 0.open 1.close 3.closetoday
                break;
            case Orders::CLOSE_TODAY_LONG:
                order.Direction = THOST_FTDC_D_Sell; //THOST_FTDC_D_Buy : THOST_FTDC_D_Sell;
                order.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday; // 0.open 1.close 3.closetoday
                break;
            case Orders::CLOSE_TODAY_SHORT:
                order.Direction = THOST_FTDC_D_Buy; //THOST_FTDC_D_Buy : THOST_FTDC_D_Sell;
                order.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday; // 0.open 1.close 3.closetoday
                break;
            default:
                return;
        }
    }
}
