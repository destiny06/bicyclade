#include "Player.hpp"

Player::Player(Client& c) : Client(c.id,c.name) {
	this->coins = 0;
}
