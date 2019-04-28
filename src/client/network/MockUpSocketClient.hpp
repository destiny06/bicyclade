#pragma once

#include "SocketClient.hpp"
#include "ServerConnectionInfo.hpp"
#include "SocketClientListener.hpp"

#include "../../generated/bicyclade.pb.h"

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
