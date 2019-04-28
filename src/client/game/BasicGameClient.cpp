#include "BasicGameClient.hpp"

BasicGameClient::BasicGameClient(SocketClient& s)
    : GameClientController(),
      socket(s),
      externalListener(NULL) {

}

BasicGameClient::~BasicGameClient(){

}

void BasicGameClient::setExternalListener(GameClientListener* listener){
    externalListener = listener;
}

void BasicGameClient::onPlayerAction(const PPlayerAction& action){
    /* TODO: Not Implemented Yet */
}

void BasicGameClient::onGameAction(const PGameAction& action){
    /* TODO: Not Implemented Yet */
}

// -----------------------------------
// GameClientController Implementation
// -----------------------------------
void BasicGameClient::putOfferingMarker(){
    /* TODO: Not Implemented Yet */
}
