#pragma once

#include "../../bom/Client.hpp"

/**
 * Events from the lobby, see ClientApplication design.
 */
class LobbyClientListener {
public:
	LobbyClientListener(){}
	virtual ~LobbyClientListener(){}

	virtual void onJoin(const Client& client) = 0;
	virtual void onQuit(const Client& client) = 0;
	virtual void onRename(const Client& client, const std::string oldName) = 0;
	virtual void onChat(const Client& client, const std::string message) = 0;
};
