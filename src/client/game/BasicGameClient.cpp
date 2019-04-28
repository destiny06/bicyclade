#include "BasicGameClient.hpp"

BasicGameClient::BasicGameClient(SocketClient& s)
    : GameClientListener(),
      GameClientController(),
      socket(s) {

}

BasicGameClient::~BasicGameClient(){

}

// -----------------------------------
// GameClientListener Implementation
// -----------------------------------
void BasicGameClient::onUpdateCoins(){
    /* TODO: Not Implemented Yet */
}

// -----------------------------------
// GameClientController Implementation
// -----------------------------------
void BasicGameClient::putOfferingMarker(){
    /* TODO: Not Implemented Yet */
}
