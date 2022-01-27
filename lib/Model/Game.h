#ifndef _GAME_H_
#define _GAME_H_

#include <vector>
#include "algorithm"
#include "Deck.h"
#include "Player.h"
#include "Croupier.h"

enum Game_State {
    NOT_STARTED=0, //the game has,'t started yes
    IN_PLAY=1, //the game is running, the players can play
    FINISHING=2 //the croupiers hand will be shown, and the win fail of the players will be computed
};
enum Action_Send{CONNECTION_ESTABLISHED,HIT,END_TURN,END_ROUND,
                 BET,ADD_FUNDS};
class Game {
private:
    Game_State game_state = NOT_STARTED;
    Deck deck = Deck();
    Croupier croupier = Croupier();
    std::vector<Player> playerList;
    size_t currentPlayer=0;
    int game_id;

public:
    // Everything related to cards and state of the game
    /**
     * @brief Constructor of Game object
     */
    Game()=default;
    Game(Player, int);
    /**
        * add a new player
        * @brief add_new_player
        * @param bank
        * @param server_id
        * @param name
        */
    void add_new_player(size_t bank,size_t server_id, std::string name);
    inline void remove_player(int id ){
        int i=0;
        for(auto &player: playerList)
        {
            if(player.get_server_id()==static_cast<size_t>(id))
            {
                playerList.erase(playerList.begin()+i);
                break;
            }
            i++;
        }
    }

    /**
     * @brief Switches the game to the next player. When no more players, lauches the end of the game
     */
    void nextPlayer();

    /**
     * @brief Adds the two first cards to each player but also to the bank.
     */
    void initial_card_distribution();
    /**
     * @brief Adds a card to the curent player.
     */
    void hit_card_current_player_next_player_if_lost();
    /**
     * @brief Returns the number of the player that has to play
     * @return which player's turn it is.
     */
    size_t get_current_player() const ;
    /**
     * @brief Determines what are the final scores of the players and sets their states accordingly.
     */
    void final_score_and_state();
    /**
         * check who win and set state
         * @brief finish_round
    */
    void finish_round();
    /**
     * @brief Getter for the deck of cards.
     * @return a copy of the deck
     */
    const Deck &get_deck() const;
    /**
     * @brief Returns a reference to the currently active player.
     * @return a reference to the player.
     */
    Player& get_current_player_object();
    /**
     * @brief Getter for the list of all the players
     * @return a copy of the list of all the players
     */
    const std::vector<Player> get_player_list() const;
    /**
     * @brief Getter for the current state of the game.
     * @return a game state
     */
    Game_State get_game_state();
    /**
     * @brief Setter for the current state of the game.
     */
    void set_game_state(Game_State);

    // Everything related to players and their scores
    /**
     * @brief ask_card Returns the last card from the deck after removing it.
     * @return a reference to a Card object
     */
    Card ask_card();
    /**
     * @brief Inserts a given Card to the current player determined by size_t currentPlayer
     */
    void insert_card_player(Card);
    /**
     * getter of the value Action Send
     * @brief getValue
     * @return value
     */
    Action_Send getValue()const;

    /**
     * getter of the croupier
     * @brief get_croupier
     * @return croupier
     */
    const Croupier get_croupier() const;
    /**
     * check if the bet is allowed, and add him
     * @brief insert_bet
     */
    void insert_bet(size_t,int);
    /**
     * reset the bet
     * @brief reset_mise
     */
    void reset_mise(Player&);
    /**
     * distributed the gains if win
     * @brief gain_distribution
     */
    void gain_distribution();
    /**
     * add amount in the bank
     * @brief insert_bank
     * @param player_to_insert_into
     * @param amount
     */
    void insert_bank(int player_to_insert_into, int amount);

    /**
     * @brief Sets the state of a player.
     * @param player to modify.
     * @param state to set.
     */
    void set_player_state(int player, Player_State state);
    /**
     * @brief Verifies if all players are ready to play.
     * @return true if so, false otherwise.
     */
    bool game_can_start();


    /**
     * @brief Getter for the players game index.
     * @return the index.
     */
    inline int get_game_id(){return game_id;}
    /**
     * @brief Getter for player at a given position.
     * @return player object.
     */
    Player& get_player_at(int);
    /**
     * @brief Resets all the stats, cards and status of all the players.
     */
    void reset_game_and_players();
private:
    Action_Send action_send;

};

#endif //_GAME_H_
