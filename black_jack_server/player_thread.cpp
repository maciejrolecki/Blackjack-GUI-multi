#include "player_thread.h"
#include "game_handler.h"
player_thread::player_thread(QTcpSocket* socket): player_socket_(socket)
{
    this->json_generator = json_gen();
    this->packet = json_packet();
    this->inperpreter= json_interpreter();
}

void player_thread::run()
{
    qDebug()<<"-----------------------------------\n"<< "Thread begin"<<"---------------------------------------\n";
    this->player_socket_= new QTcpSocket();
    if(!this->player_socket_->setSocketDescriptor(this->socket_descriptor_))
    {
        qDebug()<<"Error";
        emit error(player_socket_->error());
        return;
    }
    qDebug()<<"---------------------------\n"<<"Client connected...\n"<<"connecting slot...\n"<<"-------------------------------------\n";
    connect(player_socket_,SIGNAL(readyRead()),this,SLOT(read_in()),Qt::DirectConnection);
    connect(player_socket_,SIGNAL(disconnected()),this,SLOT(log_out()));
    qDebug()<<"---------------------------\n"<<"Client connected...\n"<<"Slot connected...\n"<<"-------------------------------------\n";
    exec();
}

void player_thread::read_in()
{
    qDebug()<<"---------------------------\n"<<"Client connected...\n"<<"Data received...\n";
    buffer=QByteArray(player_socket_->readAll());
    qDebug()<<"---> Data store in buffer...\n";
    this->packet.set_data_encap(buffer);
    qDebug()<<"---> Daata set into packet...\n";
    this->packet.un_pack_data();
    qDebug()<<"---> Data unpacked...\n";
    auto data = this->packet.get_data();
    qDebug()<<"---> Data unpacked received...\n";
    this->inperpreter.interprete_type(data);
    qDebug()<<"---> Data interpreted...\n";
    auto type = this->inperpreter.get_action();
    qDebug()<<"---> Data action received...\n";
    handle_received(data,type);


}
player_thread::player_thread(qintptr socket_descriptor, QObject* parent) :
    QThread(parent), socket_descriptor_(socket_descriptor)
{
    this->json_generator = json_gen();
    this->packet = json_packet();
    this->inperpreter= json_interpreter();
}

void player_thread::log_out(){
    this->handler_->disconnecte_player(this);
    player_socket_->deleteLater();
    exit(0);
}

void player_thread::set_handler(game_handler *h)
{
    this->handler_=h;
}

void player_thread::handle_received(QString data, Action_Send type)
{
    qDebug()<<"---> Data given to handler\n";
    switch (type) {
    case CONNECTION_ESTABLISHED :
    {
        qDebug()<<"---> Data action received is co\n";
        this->inperpreter.interprete_connection_established_basic(data);
        qDebug()<<"---> Data interpretation\n";
        auto name = this->inperpreter.get_name_send();
        qDebug()<<"---> Data content is normally the name is :"<<name <<"\n";
        user_info info;
        qDebug()<<"---> user info created...\n";
        this->handler_->create_game(name, info);
        qDebug()<<"--->  game created...\n";
        this->userName= info.nickname.toStdString();
        this->player_game_id = info.player_game_id;
        this->bank= info.amount_;
        this->db_id= info.id_;
        qDebug()<<"---> Username is:"<<userName.c_str() <<"\n";
        qDebug()<<"---> bank amount: "<<QString::number(bank)<<"\n";
        qDebug()<<"---> DB ID: "<< QString::number(db_id)<<"\n";
        qDebug()<<"---> player game id: "<< QString::number(player_game_id)<<"\n";
        break;
    }
    case HIT :{
        handler_->get_game().hit_card_current_player_next_player_if_lost();
        if(handler_->get_game().get_game_state()==Game_State::FINISHING)
        {
            this->handler_->get_game().final_score_and_state();
            this->handler_->update_data_in_db();
            this->handler_->get_game().gain_distribution();
            this->handler_->get_game().reset_game_and_players();

        }
        break;
    }
    case END_TURN:{
        handler_->get_game().nextPlayer();
        if(handler_->get_game().get_game_state()==Game_State::FINISHING)
        {
            this->handler_->get_game().final_score_and_state();
            this->handler_->update_data_in_db();
            this->handler_->get_game().gain_distribution();
            this->handler_->get_game().reset_game_and_players();
        }
        break;
    }
    case END_ROUND :
        break;
    case BET :{
        qDebug()<<"-->Bet action received...\n";
        this->inperpreter.interprete_bet(data);
        qDebug()<<"-->Interprete bet...\n";
        auto bet_data = this->inperpreter.get_bet_data();
        qDebug()<<"-->getting bet data...\n";
        int who = bet_data[1].toInt();
        qDebug()<<"-->player who bet id:"<<QString::number(who)<<"\n";
        int bet = bet_data[0].toInt();
        qDebug()<<"-->player amount bet:"<<QString::number(bet)<<"\n";
        handler_->get_game().insert_bet(who,bet);
        this->bank=this->handler_->get_game().get_player_at(who).get_bank();
        handler_->update_bank(this->player_game_id, this->bank);
        handler_->get_game().set_player_state(who,Player_State::PLAYING);
        auto can_play = handler_->get_game().game_can_start();
        if(can_play)
        {
            handler_->get_game().set_game_state(Game_State::IN_PLAY);
            handler_->get_game().initial_card_distribution();
        }
        qDebug()<<"-->Writting data to send\n";
        break;
    }
    case ADD_FUNDS :
    {
        this->inperpreter.interprete_add_funds(data);
        auto fund_data = this->inperpreter.get_fund_data();
        int who = fund_data[1].toInt();
        int amount = fund_data[0].toInt();
        handler_->get_game().insert_bank(who,amount);
        this->bank=this->handler_->get_game().get_player_at(who).get_bank();
        handler_->update_bank(this->player_game_id, this->bank);
        break;
    }
    default:
        break;
    }
    qDebug()<<"I notify every body\n";
    this->handler_->notify_everybody();
     qDebug()<<"I notify every body done\n";

}

void player_thread::writeData(Game g){
    auto &&data = json_generator.generate_json_game_info(userName,db_id,bank,g,player_game_id).str();
    qDebug()<<data.c_str();
    QString qdata= QString(data.c_str());
    this->packet.clear();
    this->packet.set_data(qdata);
    this->packet.pack_data();

    this->player_socket_->write(this->packet.get_data_encapsulated());
}
