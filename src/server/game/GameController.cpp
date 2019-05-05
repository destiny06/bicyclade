#include "GameController.hpp"

void GameController::startGame(playerMapType* playerMap) {
    this->playersMap = playerMap;

    // assigning random fixed colours

    playerMapType::iterator it = playerMap->begin();
    it->second->colour = Colour::BLACK;
    it++;
    it->second->colour = Colour::BLUE;
    it++;
    it->second->colour = Colour::YELLOW;
}
