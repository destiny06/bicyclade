#pragma once

#include "SocketClient.hpp"
#include "ServerConnectionInfo.hpp"
#include "SocketClientListener.hpp"

#include "../../generated/bicyclade.pb.h"

/**
 * Mock-up on the socket that does not connect to any actual server. Any
 * message send to the server will be directly forward back to the onMessage()
 * socket listener callback.
 *
 * For test purpose and debugging only.
 */
class MockUpSocketClient : public SocketClient {
public:
    MockUpSocketClient(ServerConnectionInfo& i, SocketClientListener& l);
    ~MockUpSocketClient();

    // -----------------------------------
    // SocketClient Implementation
    // -----------------------------------
    void connect();
    void disconnect();
    void send(proto::PContainer& message);
};
