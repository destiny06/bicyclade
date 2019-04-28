#pragma once

#include "ServerConnectionInfo.hpp"
#include "SocketClientListener.hpp"

#include "../../generated/bicyclade.pb.h"

class SocketClient {
protected:
    ServerConnectionInfo& info;
    SocketClientListener& listener;

public:
    SocketClient(ServerConnectionInfo& i, SocketClientListener& l)
        : info(i), listener(l) {
    }
    virtual ~SocketClient(){}

    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual void send(proto::PContainer& message) = 0;
};
