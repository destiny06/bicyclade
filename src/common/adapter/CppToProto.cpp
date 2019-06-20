#include "CppToProto.hpp"

#include "common/Util.hpp"
#include "bicyclade.pb.h"
#include "serveractions.pb.h"
#include "common.pb.h"

using namespace std;
using namespace proto;

PContainer CppToProto::buildStartGame(playerMapType* playersList) {
	PAction_START_GAME* start = new PAction_START_GAME();

	playerMapType::iterator it = playersList->begin();

	PPlayer* p1 = start->add_player_list();
	p1->set_allocated_name(new std::string(it->second->name));
	p1->set_colour((PColour)it->second->colour);
	it++;

	PPlayer* p2 = start->add_player_list();
	p2->set_allocated_name(new std::string(it->second->name));
	p2->set_colour((PColour)it->second->colour);
	it++;

	PPlayer* p3 = start->add_player_list();
	p3->set_allocated_name(new std::string(it->second->name));
	p3->set_colour((PColour)it->second->colour);

	PContainer answer;
	answer.set_global_action(proto::PGlobalActionType::SERVER_ACTION);
	PServerAction *act = new PServerAction();

	act->set_type(PServerActionType::START_GAME);
	act->set_allocated_action_start(start);

	answer.set_allocated_server_action(act);

	return answer;
}
