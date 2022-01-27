#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "iostream"
#include "vector"
#include "Card.h"

enum Player_State {
    PLAYING=0,//state when the player is in the game, and that the round hasn't finished yet
    WIN=1,    //state if the player won a game just by getting a higher score than the croupier
    LOSE=2,   //state if the player lost the game, meaning he went over 21
    NEUTRAL=3,//state if the player skips the round meaning he isn't playing
    STRIKE=4, //state if the player did a 21 in 2 cards and the croupier didn't
    DRAW=5,    //state if the player did a draw, meaning that he got the same score as the croupier without going over 21
    WAITING=6 //state when a player did not decide yet whether he will be playing or skipping this round
};

class Player {
private:
    std::string name="";
    size_t server_id = 0;
    std::vector<Card> hand;
    size_t mise = 0;
    size_t bank = 0;
    Player_State state;
    size_t MAX_SCORE = 21;
public:
    Player()=default;
    /**
     * @brief Constructor of Player object with which player he is.
     * 0 is default for bank
     */
    Player(Player_State state,size_t bank,size_t server_id = 0, std::string name = "");

    /**
     * @brief Returns what the player bid in the game.
     * @return the amount of the bet.
     */
    size_t get_mise() const;
    /**
     * @brief Returns the current state of the player.
     * @return players state in the game
     */
    [[nodiscard]] Player_State get_state () const;

    /**
     * @brief Get the cards that the player has in hand
     * @return the cards
     */
    [[nodiscard]] const std::vector<Card> &get_hand() const;
    /**
     * @brief Get the highest score that a player can get and not loose
     * @return the maximum score, that is a blackjack = 21
     */
    int get_max_score() const;
    /**
     * @brief Get the score that a player has with its cards.
     * @return the score of the player.
     */
    size_t get_score() const;
    /**
     * setter of state
     * @brief set_state
     */
    void set_state(Player_State);
    /**
     * setter of the mise
     * @brief set_mise
     * @param mise
     */
    void set_mise(size_t mise=0);
    /**
     * check if the bet is allowed (enough mommey) and add the bet
     * @brief insert_mise
     * @param mise
     */
    void insert_mise(size_t mise);
    /**
     *add a card in the hand of the player
     * @brief add_card
     */
    void add_card (Card );
    /**
     * @brief Verifies if the player has scored a blackjack in two cards.
     * @return true if it is the case, false otherwise.
     */
    bool strike() const;
    /**
     * return a boolean if the player beat the player in param
     * @brief beat
     * @return bool
     */
    bool beat(Player);
    /**
     * boolean to know if we are out off the range
     * @brief is_out_of_bound
     * @return boolean
     */
    bool is_out_of_bound();

    /**
     * @brief Verifies if a certain amount can be debited from the account.
     * @return true if ther is enough.
     */
    bool verify_amount (size_t );

    /**
     * @brief Modifies the bank account if the player won the current game.
     */
    void win_mise();

    /**
     * @brief Modifies the bank account if the player played a draw with the croupier.
     */
    void draw_mise();

    /**
     * @brief Adds cash to the bank of the player.
     */
    void add_cash(size_t);

    /**
     * @brief Gets the players name that is registered in the DB.
     * @return string that represents the players name/unique identifier.
     */
    const std::string get_name() const;

    /**
     * @brief Gets the id that represents the player on the DB server.
     * @return a number identifying the player.
     */
    size_t get_server_id() const;
    /**
     * add the gains for the player
     * @brief player_distribute_gains
     * @param mult
     */
    void player_distribute_gains(double mult);
    /**
     * getter of the bank
     * @brief get_bank
     * @return bank
     */
    size_t get_bank();

    /**
     * @brief Skips this round for the player, meaning the state will be set to neutral and back to normal if the player wants to play.
     */
    void skip_this_round();

    /**
     * @brief Removes all cards from a player's deck.
     */
    void remove_all_cards(){this->hand = std::vector<Card> ();};
};

#endif //_PLAYER_H_
