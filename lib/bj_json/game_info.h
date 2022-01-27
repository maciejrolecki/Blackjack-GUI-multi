#ifndef GAME_INFO_H
#define GAME_INFO_H
#include "QString"
#include "vector"
#include "array"
#include "Model/Card.h"
struct player_info
{
    std::pair<std::vector<std::string>,std::vector<std::string>> data;
public:

    player_info()=default;
    player_info(std::vector<std::string> results, std::vector<std::string> cards){data=std::make_pair(results,cards);};
    inline int get_mise(){return stoi(data.first.at(0));}
    inline int get_state(){return stoi(data.first.at(1));}
    inline int get_score(){return stoi(data.first.at(2));}
    inline int get_bank(){return stoi(data.first.at(3));}
    inline int get_id(){return stoi(data.first.at(4));}
    inline std::string get_name(){return data.first.at(5);}
    std::vector<std::string> get_cards(){return data.second;}

};

struct game_info
{
    QString game_state_;
    int current_player_;
    int croupier_score;
    std::vector<std::string>croupier_card;
    std::vector<player_info> info_players;

public:
    game_info()=default;
    game_info(QString game_state_,int current_player_,int croupier_score,std::vector<std::string>croupier_card,std::vector<player_info> players_info):
    game_state_(game_state_),current_player_(current_player_),croupier_score(croupier_score),croupier_card(croupier_card),info_players(players_info)
    {}
    inline int get_current_player(){return current_player_;}
    inline QString get_game_state(){return game_state_;}
    inline int get_c_score(){return croupier_score;}
    inline std::vector<player_info> get_info(){return info_players;}
    inline int get_nb_players(){return get_info().size();};
    inline std::vector<std::string> get_croupier_cards(){ return croupier_card;};

};

#endif // GAME_INFO_H
