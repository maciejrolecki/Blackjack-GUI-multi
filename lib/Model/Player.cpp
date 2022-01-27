#include "Player.h"

Player::Player (Player_State state,size_t bank,size_t server_id, std::string name)
{
    if(server_id!=0) {
        this->server_id = server_id;
        this->name = name;
    }
    this->bank=bank;
    this->state = state;
    this->hand = std::vector<Card> ();
}

size_t Player::get_mise () const{
    return mise;
}

Player_State Player::get_state() const {
    return state;
}

const std::vector<Card> &Player::get_hand() const {
    return hand;
}

int Player::get_max_score() const {
    return MAX_SCORE;
}

void Player::set_state(Player_State state){
    this->state=state;
}

void Player::set_mise(size_t mise){
    this->mise = mise;
}

void Player::add_card (Card card){
    this->hand.push_back (std::move(card));
}

bool Player::verify_amount (size_t mise){
    return get_bank()>=mise;
}

void Player::insert_mise(size_t mise){
    if(verify_amount(mise)) {
        set_mise(mise);
        add_cash(-mise);

    }
    else {
        set_mise(bank);
        add_cash(-bank);
    }
}

size_t Player::get_score() const{ //src = https://stackoverflow.com/a/19409652
    if(strike())return MAX_SCORE;
    int total = 0;
    size_t nbAces = 0;
    for(auto it = std::begin(hand); it != std::end(hand); ++it) {
        if(it->get_value()==ACE)
            nbAces++;
        else {
            if(it->get_value_card()>10)
                total += 10;
            else total += it->get_value_card();
        }
    }
    if(nbAces>0){
        if((total+11+(nbAces-1)>21))
            total+=nbAces-1;
        else total+=11+(nbAces-1);
    }
    return total;
}

bool Player::strike() const{
    if(get_hand().size()==2)
        if(((get_hand().at(0).get_value()==10) && (get_hand().at(1).get_value()==11))
                || ((get_hand().at(1).get_value()==10) && (get_hand().at(0).get_value()==11)))
            return true;
    return false;
}
bool Player::beat (Player player){
    return (this->get_score() > player.get_score() && this->get_score() <= this->MAX_SCORE) ||
            (this-> get_score() <= this->MAX_SCORE && player.get_score() > this->MAX_SCORE);
}

bool Player::is_out_of_bound(){
    return (this->get_score() >= this->MAX_SCORE);
}

const std::string Player::get_name() const{
    return this->name;
}

size_t Player::get_server_id() const {
    return this->server_id;
}

void Player::add_cash(size_t amount){
    this->bank+=amount;
}

void Player::player_distribute_gains(double mult){
    add_cash((double)(get_mise()*mult));
    set_mise();
}


size_t Player::get_bank(){
    return bank;
}

