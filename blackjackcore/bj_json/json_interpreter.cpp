#include "json_interpreter.h"

void json_interpreter::interprete_type(QString content)
{
    QJsonDocument document = QJsonDocument::fromJson(content.toUtf8());
    if(!document.isEmpty())
    {
        qDebug()<<"Doc is not empty...\n";
        QJsonObject object_from_doc = document.object();
        QJsonValue type = object_from_doc.value("Type");
        qDebug()<<"--->Type extrated...\n";
        set_action(type.toString());
        qDebug()<<get_action();
    }
}

void json_interpreter::set_action(QString type)
{
    std::array<QString, 6> types={"CONNECTION_ESTABLISHED","HIT","END_TURN","END_ROUND","BET","ADD_FUNDS"};
    std::array<Action_Send,6> types_e={CONNECTION_ESTABLISHED,HIT,END_TURN,END_ROUND,BET,ADD_FUNDS};
    for(int i=0;i<6;i++)
    {
        if(type==types[i])
        {
            action = types_e[i];
        }
    }

}

Action_Send json_interpreter::get_action()
{
    return action;
}
void json_interpreter::interprete_connection_established_basic(QString content)
{

    QJsonDocument document = QJsonDocument::fromJson(content.toUtf8());
    if(!document.isEmpty())
    {
        auto doc_object = document.object();
        auto user_info = doc_object.value("User").toObject();
        name_send= user_info.value("name").toString();

    }

}
void json_interpreter::interprete_connection_established_game(QString content)
{
    connection_established_data = std::array<QString,4>();
    QJsonDocument document = QJsonDocument::fromJson(content.toUtf8());
    qDebug()<< document;
    if(!document.isEmpty())
    {
        qDebug()<<"bonjourrr";
        auto doc_object = document.object();
        auto user_info = doc_object.value("User").toObject();
        connection_established_data[0]= user_info.value("name").toString();
        connection_established_data[1]=user_info.value("db_id").toString();
        connection_established_data[2]=user_info.value("bank").toString();
        connection_established_data[3]=user_info.value("player_game_id").toString();
        auto game_inf = doc_object.value("Game").toObject();
        QString game_state = game_inf.value("state").toString();
        int curr_play_id = game_inf.value("currentPlayer").toInt();
        auto croupier = game_inf.value("croupier").toObject();
        int score_croupier = croupier.value("score").toInt();
        QJsonArray croupier_cards = croupier["cards"].toArray();
        std::vector<std::string> v_croupier_cards;
        for (auto card : croupier_cards ) {
            v_croupier_cards.push_back(card.toObject().value("Value").toString().toStdString()+card.toObject().value("Color").toString().toStdString().at(0));
        }
        auto players = doc_object.value("Players").toArray();
        std::vector<player_info> players_data;
        for (auto player : players ) {
            std::vector<std::string> results_player;
            results_player.push_back(player.toObject().value("mise").toString().toStdString());
            results_player.push_back(player.toObject().value("state").toString().toStdString());
            results_player.push_back(player.toObject().value("score").toString().toStdString());
            results_player.push_back(player.toObject().value("bank").toString().toStdString());
            results_player.push_back(player.toObject().value("id").toString().toStdString());
            results_player.push_back(player.toObject().value("name").toString().toStdString());
            std::vector<std::string> player_cards;
            for (auto card : player.toObject().value("playerCards").toArray()) {
                player_cards.push_back(card.toObject().value("Value").toString().toStdString()+card.toObject().value("Color").toString().toStdString().at(0));
            }
            players_data.push_back(player_info(results_player,player_cards));
        }
        this->game=game_info(game_state,curr_play_id,score_croupier,v_croupier_cards,players_data);
    }
}
void json_interpreter::interprete_hit(QString)

{

}
void json_interpreter::interprete_end_turn(QString)
{

}
void json_interpreter::interprete_end_round(QString)
{

}
void json_interpreter::interprete_bet(QString content)
{
    this->bet_data = std::array<QString,2>();
 QJsonDocument document = QJsonDocument::fromJson(content.toUtf8());
 if(!document.isEmpty())
 {
    auto doc_to_object = document.object();
    bet_data[0]= doc_to_object.value("Amount").toString();
    bet_data[1]= doc_to_object.value("Who").toString();
 }

}
void json_interpreter::interprete_add_funds(QString content)
{
    this->fund_data = std::array<QString,2>();
 QJsonDocument document = QJsonDocument::fromJson(content.toUtf8());
 if(!document.isEmpty())
 {
    auto doc_to_object = document.object();
    fund_data[0]= doc_to_object.value("Amount").toString();
    fund_data[1]= doc_to_object.value("Who").toString();
 }
}
