#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QTcpSocket>
#include <QObject>

#include "Model/Game.h"

#include "bj_json/json_interpreter.h"
#include "bj_json/json_gen.h"
#include "bj_packet_ip/json_packet.h"
#include "bj_json/game_info.h"

class client_connection_window;
class black_jack;

class Controller: public QObject
{
    Q_OBJECT
public:
    /**
     * constructor of the controller
     * @brief Controller
     * @param parent
     */
    Controller(QObject *parent = nullptr);

    /**
     * launch the connexion between the serveur and the client
     * @brief conection_serv
     * @param name
     */
    void conection_serv(QString name);

    /**
     * write the type of message HIT in the json
     * @brief button_draw
     */
    void button_draw();

    /**
     * write the type of message END_TOUR in the json
     * @brief button_stay
     */
    void button_stay();

    /**
     * write the type of message ADD_FUNDS in the json
     * @brief button_add
     * @param amount
     */
    void button_add(int amount);

    /**
     * write the type of message BET in the json
     * @brief button_bet
     * @param amount
     */
    void button_bet(int amount);
    /**
     * launch the view of the connection for the player
     * @brief start
     */
    void start();

    /**
     * setter of connection
     * @brief set_connection_window
     * @param window
     */
    void set_connection_window(client_connection_window* window);
    //bool checkBank();
    /**
     * apply the change for the game
     * @brief apply_game_info
     */
    void apply_game_info();
    /**
     * getter of game_info
     * @brief get_game_info
     * @return game
     */
    inline game_info get_game_info(){ return game;};
    /**
     * getter of player name
     * @brief get_player_name
     * @return name of the player
     */
    inline QString get_player_name(){ return interpreter.get_connection_established_data().at(0);};
    /**
     * getter of player bank
     * @brief get_player_bank
     * @return bank of the player
     */
    inline QString get_player_bank(){ return interpreter.get_connection_established_data().at(2);};
    /**
     * getter of the index of the player
     * @brief get_player_game_id
     * @return index of the player
     */
    inline int get_player_game_id(){ return interpreter.get_connection_established_data().at(3).toInt();};



public slots:
    /**
     * read the incomming information from the serveur
     * @brief read
     */
    void read();
    /**
     * write the information/type in the json for the serveur
     * @brief write_data
     * @param action
     */
    void write_data(Action_Send action);
private:

      QTcpSocket *socket;
      game_info game;
      json_packet packet;
      json_interpreter interpreter;
      json_gen gen;
      QByteArray buffer;
      QString username;
      size_t game_user_id;
      client_connection_window* connection_window;
      black_jack* game_window;
      int te = 0;
      bool is_launched = false;

};

#endif // CONTROLLER_H
