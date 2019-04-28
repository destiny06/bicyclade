#pragma once

#include "../../generated/bicyclade.pb.h"

class SocketClientListener {
public:
    SocketClientListener(){}
    virtual ~SocketClientListener(){}

    virtual void onOpen() = 0;
    virtual void onClose() = 0;
    virtual void onMessage(proto::PContainer& message) = 0;
    virtual void onFail() = 0;
};
