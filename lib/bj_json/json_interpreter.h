#ifndef JSON_INTERPRETER_H
#define JSON_INTERPRETER_H
#include "Model/Game.h"
#include "game_info.h"
#include "QString"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
class json_interpreter
{
    Action_Send action;
    void set_action(QString type);
    std::array<QString,4> connection_established_data;
    std::array<QString,2> bet_data;
    std::array<QString,2> fund_data;

    QString name_send;
    game_info game;

public:
    json_interpreter()=default;
    void interprete_type(QString content);
    void interprete_connection_established_basic(QString content);
    void interprete_connection_established_game(QString content);
    void interprete_hit(QString);
    void interprete_end_turn(QString);
    void interprete_end_round(QString);
    void interprete_bet(QString);
    void interprete_add_funds(QString);
    Action_Send get_action();
    inline std::array<QString,4> get_connection_established_data(){return connection_established_data;}
    inline QString get_name_send(){return name_send;}
    inline game_info get_game_info(){ return game;}
    inline std::array<QString,2> get_bet_data(){return bet_data;}
    inline std::array<QString,2> get_fund_data(){return fund_data;}

};

#endif // JSON_INTERPRETER_H
