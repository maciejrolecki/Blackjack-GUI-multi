#ifndef JSON_GEN_H
#define JSON_GEN_H
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/optional.hpp>
#include <sstream>
#include <cstdlib>
#include "Model/Game.h"
using boost::property_tree::ptree;
class json_gen
{
    void add_cards(ptree&, std::vector<Card>cards, int);
    void add_players(ptree&, std::vector<Player>);

public:
    json_gen()=default;
    std::stringstream & generate_json_user_info(std::string name);
    std::stringstream & generate_json_game_info(std::string name,size_t db_id,size_t bank,Game,int player_game_id);
    std::stringstream & generate_hit();
    std::stringstream & generate_hit(Card&);
    std::stringstream & generate_end_turn();
    std::stringstream & generate_end_round();
    std::stringstream & generate_bet(int who,int amount);
    std::stringstream & generate_add_funds(int who,int amount);


};

#endif // JSON_GEN_H
