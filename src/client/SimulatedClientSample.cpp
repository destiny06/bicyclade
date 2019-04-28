#include "application/ClientApplication.hpp"
#include "application/ClientApplicationFactory.hpp"

#include <iostream>

int main() {
    std::cout << "-------------------------------\n";
    std::cout << "---- SimulatedClientSample ----\n";
    std::cout << "-------------------------------\n";

    ServerConnectionInfo info;
    info.host = "localhost";
    info.port = "9002";
    ClientApplication *app = ClientApplicationFactory::CreateWithWebSocket(info);
    std::cout << "ClientApplication -- Initialized\n";

    app->start();
    std::cout << "ClientApplication -- Started\n";

    int retry = 5;
    while(app->getLobbyController() == NULL){
        retry--;
        std::cout << "ClientApplication -- Waiting...("<< retry <<")\n";
        sleep(1);
        if(retry == 0){
            break;
        }
    }

    app->getLobbyController()->join();
    std::cout << "ClientApplication -- Join lobby\n";

    std::string pseudo = "Guest#1234";
    app->getLobbyController()->rename(pseudo);
    std::cout << "ClientApplication -- Chose name\n";

    app->stop();
    std::cout << "ClientApplication -- Stopped\n";

    retry = 5;
    while(app->getLobbyController() != NULL){
        retry--;
        std::cout << "ClientApplication -- Waiting...("<< retry <<")\n";
        sleep(1);
        if(retry == 0){
            break;
        }
    }

    delete app;
    app = NULL;
    std::cout << "ClientApplication -- Deleted\n";

    return 0;
}
