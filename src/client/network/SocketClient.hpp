#pragma once

#include "ServerConnectionInfo.hpp"
#include "SocketClientListener.hpp"

#include "bicyclade.pb.h"

/**
 * SocketClient interface is designed to dissociate the ClientApplication with
 * which way of transmitting messages to the server is used.
 *
 * The ClientApplication will send messages to the server using a SocketClient
 * implementation and will act as a SocketClientListener to retrieve and manage
 * messages from the server.
 */
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
    virtual void send(const proto::PContainer& message) = 0;
};
