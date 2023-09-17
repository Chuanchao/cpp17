//
// Created by ChuanchaoLyu on 2023/9/11.
//


#include "MarketFeed.h"
#include "config.h"

namespace gateway{

    MarketFeed::~MarketFeed() noexcept {
        _logger->info("MarketFeed Closed!");
    }

    void MarketFeed::init(const std::string & file) {
        _feedgw = CTPFeedGateway::CreateCTPFeedApi();
        _feedgw->RegisterConsumer(this);
        _feedgw->init(file);
        Config config(file);
        auto tport = config.pInt("tickport");
        auto cport = config.pInt("candleport");
        _pubtick = make_shared<utility::zmqPub>(ctx,tport);
    }


    void MarketFeed::ProcessTickData(const datafeed::TickData & tick) {
        if(!isvalidtick(tick)) return;
        auto ptick = make_shared<datafeed::TickData>(tick);
        _pubtick->PutInfo(ptick);
        _logger->info("{}",tick.DebugString());
    }


    bool MarketFeed::isvalidtick(const datafeed::TickData &) {
        return true;
    }

    void MarketFeed::Subscribe(const std::vector<std::string> & insts) {
        if(_feedgw){
            _feedgw->SubScribe(insts);
        } else{
            _logger->error("MarketFeed:: subscribe failed!'");
        }
    }

    void MarketFeed::Unsubscribe(const std::vector<std::string> & insts) {
        if(_feedgw){
            _feedgw->UnsubScribe(insts);
        } else{
            _logger->error("MarketFeed:: unsubscribe failed!'");
        }
    }

    std::string MarketFeed::GetTradingDay() {
        return _feedgw->GetTradingDay();
    }

}
