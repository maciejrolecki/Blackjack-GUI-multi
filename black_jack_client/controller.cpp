#include "controller.h"
#include "client_connection_window.h"
#include "black_jack.h"
#include "QHostAddress"
Controller::Controller(QObject *parent): QObject(parent)
{
    socket = new QTcpSocket();
    this->gen = json_gen();
    this->packet = json_packet();
    this->interpreter= json_interpreter();
    connect(socket,SIGNAL(readyRead()),this,SLOT(read()),Qt::DirectConnection);
}

void Controller::start(){
    this->set_connection_window( new client_connection_window(this));
    connection_window->show();
}
void Controller::set_connection_window(client_connection_window* window){
    this->connection_window = window;
    this->connection_window->set_controller(this);
}

void Controller::conection_serv(QString name){
    socket->connectToHost("localhost",2021);
    qDebug()<<"User name "<< name;
    this->username=name;
    write_data(CONNECTION_ESTABLISHED);
}

void Controller::button_draw(){
    write_data(Action_Send::HIT);
}
void Controller::button_stay(){
    write_data(Action_Send::END_TURN);
}
void Controller::button_add(int amount){
    te=amount;
    write_data(Action_Send::ADD_FUNDS);
}
void Controller::button_bet(int amount){
    te=amount;
    write_data(Action_Send::BET);
}


void Controller::read(){
    buffer.clear();
    buffer=QByteArray(socket->readAll());
    this->packet.clear();
    this->packet.set_data_encap(buffer);
    this->packet.un_pack_data();
    QString dt=QString(this->packet.get_data());
       qDebug()<<"data";
    qDebug()<<dt;
    this->interpreter.interprete_type(dt);
    this->interpreter.interprete_connection_established_game(dt);
    this->game = this->interpreter.get_game_info();
    qDebug()<< this->interpreter.get_game_info().info_players.at(0).get_bank();
        if(is_launched){
           // qDebug()<<this->game.info_players.at(0).get_bank();
            this->game_window->set_controller(this);
            apply_game_info();
        }else{
            this->connection_window->close();
            this->game_window = new black_jack(this);
            this->game_window->set_controller(this);
            is_launched = true;
            apply_game_info();
            game_window->show();
        }
}

void Controller::write_data(Action_Send action){
    this->packet.clear();
    QString data;
    switch (action) {
    case CONNECTION_ESTABLISHED:{
        auto temp= this->gen.generate_json_user_info(username.toStdString()).str();
        data =QString(temp.c_str());
        break;
    }
    case HIT:{
        auto temp = this->gen.generate_hit().str();
        data = QString(temp.c_str());
        break;
    }
    case END_TURN:{
        auto temp=this->gen.generate_end_turn().str();
        data = QString(temp.c_str());
        break;
    }
    case END_ROUND:{
        auto temp=this->gen.generate_end_round().str();
        data = QString(temp.c_str());
        break;
    }
    case BET:{
        auto temp=this->gen.generate_bet(get_player_game_id(),te).str();
        data = QString(temp.c_str());
        break;
    }
    case ADD_FUNDS:{
        auto temp=this->gen.generate_add_funds(get_player_game_id(),te).str();
        data = QString(temp.c_str());
        break;
    }
    default:
        break;
    }
    this->packet.set_data(data);
    this->packet.pack_data();
    socket->write(this->packet.get_data_encapsulated());
}

void Controller::apply_game_info()
{
    game_window->apply_game_info();
};

//bool Controller::checkBank(){
//if(game){

//    }
//}

