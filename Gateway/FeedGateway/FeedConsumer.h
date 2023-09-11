//
// Created by Chuanchao Lyu on 2023/9/8.
//

#ifndef ORDERTEST_FEEDCONSUMER_H
#define ORDERTEST_FEEDCONSUMER_H

#include "datafeed.pb.h"

namespace gateway{

    class FeedConsumer{
    public:
        virtual ~FeedConsumer(){};
        virtual void ProcessTickData(const datafeed::TickData&)=0;
    };

}


#endif //ORDERTEST_FEEDCONSUMER_H
