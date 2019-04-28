#include "application/ClientApplication.hpp"
#include "application/ClientApplicationFactory.hpp"

#include <iostream>

int main() {
    ServerConnectionInfo info;
    info.host = "localhost";
    info.port = "9002";

    ClientApplication *app = ClientApplicationFactory::CreateWithWebSocket(info);
    bool done = false;
    std::string input;

    while (!done) {
        std::cout << "Enter Command: ";
        std::getline(std::cin, input);

        if (input == "exit") {
            done = true;
        } else if (input == "help") {
            std::cout
                << "\nCommand List:\n"
                << "start: Start the client\n"
                << "stop: Stop the client\n"
                << "join: Join the game\n"
                << "quit: Quit the game\n"
                << "name <new_name>: Change in-game pseudo\n"
                << "chat <msg>: Send a message to everyone\n"
                << "help: Display this help text\n"
                << "exit: Exit the program\n"
                << std::endl;
        } else if (input.substr(0,5) == "start") {
            app->start();
            /* TODO: Wait for callback */
        } else if (input.substr(0,4) == "stop") {
            app->stop();
            /* TODO: Wait for callback */
        } else if (input.substr(0,4) == "join") {
            if(app->getLobbyController() == NULL){
                std::cout << "> You must start the client before using this command." << std::endl;
            } else {
                app->getLobbyController()->join();
            }
            /* TODO: Wait for callback */
        } else if (input.substr(0,4) == "quit") {
            if(app->getLobbyController() == NULL){
                std::cout << "> You must start the client before using this command." << std::endl;
            } else {
                app->getLobbyController()->quit();
            }
            /* TODO: Wait for callback */
        } else if (input.substr(0,4) == "name") {
            if(app->getLobbyController() == NULL){
                std::cout << "> You must start the client before using this command." << std::endl;
            } else {
                std::stringstream ss(input);
                std::string cmd;
                std::string name;
                ss >> cmd >> name;

                app->getLobbyController()->rename(name);
            }
            /* TODO: Wait for callback */
        } else if (input.substr(0,4) == "chat") {
            if(app->getLobbyController() == NULL){
                std::cout << "> You must start the client before using this command." << std::endl;
            } else {
                std::stringstream ss(input);
                std::string cmd;
                std::string message;
                ss >> cmd;
                std::getline(ss,message);

                app->getLobbyController()->chat(message);
            }
            /* TODO: Wait for callback */
        } else {
            std::cout << "> Unrecognized Command" << std::endl;
        }
    }

    return 0;
}
