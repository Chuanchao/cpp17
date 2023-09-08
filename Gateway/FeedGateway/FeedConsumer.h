//
// Created by Chuanchao Lyu on 2023/9/8.
//

#ifndef ORDERTEST_FEEDCONSUMER_H
#define ORDERTEST_FEEDCONSUMER_H

#include "ctpData.h"

namespace gateway{

    class FeedConsumer{
    public:
        virtual ~FeedConsumer()=0;
        virtual void ProcessTickData()=0;
    };
}


#endif //ORDERTEST_FEEDCONSUMER_H
