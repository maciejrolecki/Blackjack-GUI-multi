#include "Game.h"
// Si un joueur a 21 en 2 cartes, et que la banque non, il reçois 1.5 ce qu'il a parié
// Si la banque a 21 en 2 cartes, toutes les personnes qui n'ont pas 21 en 2 cartes ont perdu
void Game::add_new_player(size_t bank,size_t server_id, std::string name){
    if(this->get_game_state()==IN_PLAY||this->get_game_state()==FINISHING)
        playerList.push_back(Player(NEUTRAL,bank,server_id,name));
    else     playerList.push_back(Player(WAITING,bank,server_id,name));
}

Game::Game(Player player,int id)
{
    this->game_id=id;
    playerList.reserve(7);
    playerList.push_back(std::move(player));
}

void Game::reset_game_and_players(){
    set_game_state(NOT_STARTED);
    for(auto &i : playerList){
        i.remove_all_cards();
        i.set_state(WAITING);
        i.set_mise(0);

    }
    croupier.remove_all_cards();
    currentPlayer=0;
}

void Game::gain_distribution(){

    for(auto & i : playerList)
    {
        switch (i.get_state()) {
        case WIN :{
            i.player_distribute_gains(2);
            break;
        };
        case DRAW : {
            i.player_distribute_gains(1);
            break;
        };
        case LOSE :{
            i.player_distribute_gains(0);
            break;
        };
        case STRIKE :{
            i.player_distribute_gains(2.5);
            break;
        };
        default:{};
        }
    }
}

void Game::final_score_and_state(){
    croupier.pick(deck);
    for(auto i : playerList)
    {
        if(i.is_out_of_bound()) i.set_state(LOSE);
        else if(croupier.strike())
            if(i.strike()) i.set_state(DRAW);
            else i.set_state(LOSE);
        else if(i.strike())i.set_state(STRIKE);
        else if(i.get_score()>croupier.get_score()) i.set_state(WIN);
        else i.set_state(LOSE);
    }
    //gain_distribution();
}

void Game::hit_card_current_player_next_player_if_lost(){
    get_current_player_object().add_card(deck.hit());
    if(get_current_player_object().get_score()>21){
        get_current_player_object().set_state(LOSE);
        nextPlayer();
    }else if(get_current_player_object().get_hand().size() == 7){
        get_current_player_object().set_state(WIN);
        nextPlayer();
    }
}

const Deck &Game::get_deck() const {
    return deck;
}

const Croupier Game::get_croupier() const {
    return croupier;
}

const std::vector<Player> Game::get_player_list() const {
    return playerList;
}

size_t Game::get_current_player() const {
    return currentPlayer;
}
Player& Game::get_current_player_object() {
    return playerList.at(currentPlayer);
}

Card Game::ask_card(){
    return deck.hit();
}
void Game::insert_card_player(Card card){
    playerList.at(currentPlayer).add_card(std::move(card));
}

//A verifier methode
void Game::nextPlayer(){
    currentPlayer++;
    if(currentPlayer<playerList.size()){
        if(get_current_player_object().get_state() != PLAYING)nextPlayer();
    } else
        this->set_game_state(FINISHING);
}

void Game::finish_round(){
    final_score_and_state();
}

void Game::insert_bank(int player_to_insert_into, int amount)
{
    playerList.at(player_to_insert_into).add_cash(amount);
}
void Game::initial_card_distribution(){
    for(int i = 0;i<2;i++)
        for (size_t i = 0; i < playerList.size(); i++) playerList.at(i).add_card(ask_card());
    croupier.add_card(ask_card());
}

void Game::insert_bet(size_t player,int  bet){
    playerList.at(player).insert_mise(bet);
}

void Game::reset_mise(Player& player){
    player.set_mise(0);
}

Game_State Game::get_game_state(){
    return this->game_state;
}

void Game::set_game_state(Game_State game_state){
    this->game_state = game_state;
}

Action_Send Game::getValue()const{
    return action_send;
}

bool Game::game_can_start()
{
    size_t can_player=0;
    std::for_each(playerList.begin(),playerList.end(),[&can_player](Player p){
        if(p.get_state()==Player_State::PLAYING)
        {
            can_player++;
        }
    });
    return can_player==playerList.size();
}

void Game::set_player_state(int player, Player_State state)
{
    playerList.at(player).set_state(state);
}

Player& Game::get_player_at(int index)
{
    return playerList.at(index);
}

