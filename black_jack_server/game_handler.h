#ifndef GAME_HANDLER_H
#define GAME_HANDLER_H
#include "Model/Game.h"
#include "vector"
#include "QTcpServer"
#include "player_thread.h"
#include "db_connexion.h"
class bj_tcp_server;
/**
 * @brief The game manager class.
 */
class game_handler
{
Game bj_game;
std::vector<player_thread*> player_threads;
bj_tcp_server * server_;
db_connexion connexion;
public:
    /**
     * @brief Constructor of game_handler
     */
    game_handler(bj_tcp_server*);
    /**
     * @brief Verfies how many players there are on the thread.
     * @return true if 7 or more, false otherwise.
     */
    bool server_is_Full();
    /**
     * @brief Verifies if the game is running.
     * @return true if so, false otherwise.
     */
    bool is_running();
    /**
     * @brief Creates a new thread for a player
     * @param handler
     */
    void creat_player_thread(qintptr &handler);
    /**
     * @brief Starts the last thread that was registered in the list?
     */
    void start_last_thread();
    /**
     * @brief Creates a game to manage with the data of the first person to connect.
     * @param name of the user.
     */
    void create_game(QString name, user_info&);
    /**
     * @brief Getter for game object.
     * @return a game.
     */
    Game& get_game();
    /**
     * @brief Updates the amount that is registered in the bank in the db.
     */
    void update_bank(int,int);
    /**
     * @brief Updates player scores int the db.
     */
    void update_player_in_db(int,int,QString,int);
    /**
     * @brief Informs all the other player threads that there were changes to take note of.
     */
    void notify_everybody();
    /**
     * @brief update_data_in_db
     */
    void update_data_in_db();
    /**
     * @brief Disconnects a player and removes the thread.
     */
    void disconnecte_player(player_thread*);
    /**
    * @brief Returns the status to register in db related to win status.
    * @param a status in form of int(game_status).
    * @return what to register in db.
    */
   std::string get_win_from_int(int a);



private:
   bool game_running;

};

#endif // GAME_HANDLER_H
