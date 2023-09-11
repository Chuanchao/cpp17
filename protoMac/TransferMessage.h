//
// Created by Chuanchao Lyu on 2023/8/24.
//

#ifndef ORDERTEST_TRANSFERMESSAGE_H
#define ORDERTEST_TRANSFERMESSAGE_H

#include <memory>
#include <zmq.hpp>
#include "transfer_message.pb.h"


inline std::shared_ptr<google::protobuf::Message> GetMessageFromTransferMessage(const transfer::TransferMessage& transfermessage){
    std::shared_ptr<google::protobuf::Message> message = nullptr;
    const google::protobuf::Descriptor* descriptor = google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(transfermessage.message_name());
    if (descriptor)
    {
        const google::protobuf::Message* prototype = google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
        if (prototype)
        {
            message = std::shared_ptr<google::protobuf::Message>(prototype->New());
            message->ParseFromString(transfermessage.message_content());
        }
    }
    return message;
}

inline void GetTransferMessageFromMessage(std::shared_ptr<google::protobuf::Message> &message, transfer::TransferMessage &transferMessage){
    transferMessage.set_message_name(message->GetDescriptor()->full_name());
    transferMessage.set_message_content(message->SerializeAsString());
}

inline std::shared_ptr<google::protobuf::Message> GetMessageFromZmqMessage(zmq::message_t &zmqMessage)
{
    transfer::TransferMessage transferMessage;
    transferMessage.ParseFromArray(zmqMessage.data(), zmqMessage.size());
    if(!transferMessage.IsInitialized())
    {
        return nullptr;
    }

    return GetMessageFromTransferMessage(transferMessage);
}

inline void GetZmqMessageFromMessage(std::shared_ptr<google::protobuf::Message> &message, zmq::message_t &zmqMessage)
{
    transfer::TransferMessage transferMessage;
    GetTransferMessageFromMessage(message, transferMessage);
    zmqMessage.rebuild(transferMessage.SerializeAsString().c_str(), transferMessage.SerializeAsString().size());
}
inline bool isEmptyMessage(std::shared_ptr<google::protobuf::Message>& message){
    return message->GetDescriptor()->full_name() == transfer::ResponseEmptyMessage::descriptor()->full_name();
}

#endif //ORDERTEST_TRANSFERMESSAGE_H
