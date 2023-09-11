//
// Created by Chuanchao Lyu on 2023/8/28.
//

#ifndef ORDERTEST_ORDERGATEWAYLISTENER_H
#define ORDERTEST_ORDERGATEWAYLISTENER_H

#include <google/protobuf/message.h>
#include <memory>

namespace gateway{
    class OrderGatewayListener{
    public:
        using Message = google::protobuf::Message;
        virtual ~OrderGatewayListener()=default;
        virtual void OnOrderFill(std::shared_ptr<Message>) = 0;
        virtual void OnError(std::shared_ptr<Message>) = 0;
        virtual void OnOrderStatusUpdate(std::shared_ptr<Message>) = 0;
    };
}



#endif //ORDERTEST_ORDERGATEWAYLISTENER_H
