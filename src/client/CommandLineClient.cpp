#include "application/ClientApplication.hpp"
#include "application/ClientApplicationFactory.hpp"

#include <iostream>

/**
 * CommandLineClient is a program that run a client on which you can directly
 * interact with the console using commands.
 *
 * Command List:
 * - start: Start the client
 * - stop: Stop the client
 * - join: Join the game
 * - quit: Quit the game
 * - name <new_name>: Change in-game pseudo
 * - chat <msg>: Send a message to everyone
 * - help: Display this help text
 * - exit: Exit the program
 */

class SocketEventsLogger : public SocketClientListener {
public:
    SocketEventsLogger(){
    }
    ~SocketEventsLogger(){
    }

    // -----------------------------------
    // SocketClientListener Implementation
    // -----------------------------------
    void onOpen(){
        std::cout << "[Socket-Logger]: Connection opened\n";
    }

    void onClose(){
        std::cout << "[Socket-Logger]: Connection closed\n";
    }

    void onMessage(const proto::PContainer& message){
        std::string s;
        message.SerializeToString(&s);

        std::string debug(message.DebugString());
        for(int i=0; i<debug.size(); i++){
            if(debug[i] == '\n'){
                debug[i] = ' ';
            }
        }
        std::cout << "[Socket-Logger]: Message from server: "<< debug << "\n";
    }

    void onFail(){
        std::cout << "[Socket-Logger]: Error - \n";
    }
};

class LobbyEventsLogger : public LobbyClientListener {
public:
    LobbyEventsLogger(){
    }
    ~LobbyEventsLogger(){
    }

    // -----------------------------------
    // LobbyClientListener Implementation
    // -----------------------------------
    void onJoin(const Client& client){
        std::cout << "[Lobby]: <" << client.name << "> joined the room.\n";
    }

    void onQuit(const Client& client){
        std::cout << "[Lobby]: <" << client.name << "> left the room. \n";
    }

    void onRename(const Client& client, const std::string oldName){
        std::cout << "[Lobby]: <" << oldName << "> is now known as <" << client.name << ">. \n";
    }

    void onChat(const Client& client, const std::string message){
        std::cout << "[Lobby]: [" << client.name << "]: " << message << "\n";
    }
};

int main() {
    ServerConnectionInfo info;
    info.host = "localhost";
    info.port = "9002";

    SocketEventsLogger socketLogger;
    LobbyEventsLogger lobbyLogger;
    ClientApplication *app = ClientApplicationFactory::CreateWithWebSocket(info);
    app->setExternalSocketListener(&socketLogger);
    app->setExternalLobbyListener(&lobbyLogger);
    bool done = false;
    std::string input;

    while (!done) {
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

    delete app; // Free the app before leaving

    return 0;
}
