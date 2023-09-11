//
// Created by ChuanchaoLyu on 2023/9/11.
//

#ifndef ORDERTEST_TICKFEED_H
#define ORDERTEST_TICKFEED_H

#include "zmqModels.h"
#include "CTPFeedGateway.h"

namespace gateway{

    class MarketFeed:public FeedConsumer, private LoggerBase{
    public:
        MarketFeed()=default;
        ~MarketFeed() override;
        void init(const std::string&);
        void Subscribe(const std::vector<std::string>&);
        void Unsubscribe(const std::vector<std::string>&);
    private:
        //void genCandles();
        bool isvalidtick(const datafeed::TickData&);
        void ProcessTickData(const datafeed::TickData&) override;
    private:
        zmq::context_t ctx{1};
        std::shared_ptr<CTPFeedGateway> _feedgw{nullptr};
        std::shared_ptr<utility::zmqPub> _pubtick{nullptr};
        //std::shared_ptr<utility::zmqPub> _pubcandle;

    };



}







#endif //ORDERTEST_TICKFEED_H
