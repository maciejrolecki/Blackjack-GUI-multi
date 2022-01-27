#include "game_handler.h"

game_handler::game_handler(bj_tcp_server*server): server_(server)
{
    this->game_running=false;
    this->connexion=db_connexion();
}
void game_handler::creat_player_thread(qintptr &handler)
{
    this->player_threads.push_back(new player_thread(handler,reinterpret_cast<QTcpServer*>(this->server_)));
    this->player_threads.back()->set_handler(this);
}
void game_handler::start_last_thread()
{
    this->player_threads.back()->start();
}

bool game_handler::server_is_Full(){
    return player_threads.size()==7;
}
bool game_handler::is_running(){
    return game_running;
}
void game_handler::create_game(QString name, user_info& info)
{
    //QStack <db_connexion * > stack;
    //stack.push(db_connexion());

    if(!game_running)
    {
        if(connexion.db_is_open())
        {
            qDebug()<<"DB ouvert...\n";
         //   stack.top()->db_connexion();
           // stack.top()->checkUser(name,info);

            this->connexion.checkUser(name,info);

            auto player = Player(Player_State::WAITING,info.amount_,info.id_,info.nickname.toStdString());
            auto game_id= this->connexion.insert_get_game_id();
            this->bj_game =Game(player, game_id);
           // connexion.insert_player_score(1,1,21,"WIN",100);
            this->game_running=true;
        }
    }else
    {
        qDebug()<<"Game running...\n";
        this->connexion.checkUser(name, info);
         qDebug()<<"Check user done...\n";
        this->bj_game.add_new_player(info.amount_,info.id_,info.nickname.toStdString());
          qDebug()<<"Adding user done...\n";
    }
    for(size_t i = 0;i< bj_game.get_player_list().size();i++){
        std::string nm = bj_game.get_player_list().at(i).get_name();
        if(std::strcmp(nm.c_str(),info.nickname.toStdString().c_str())){
            info.player_game_id= i;
        }
    }
}
Game& game_handler::get_game()
{
    return bj_game;
}

void game_handler::update_bank(int id_player, int amount)
{
    this->connexion.update_bank_player(id_player,amount);
}

void game_handler::notify_everybody()
{
    std::for_each(player_threads.begin(),player_threads.end(),
                  [this](player_thread*thread){thread->writeData(this->bj_game);});
}
void game_handler::update_data_in_db()
{
    auto players = bj_game.get_player_list();
    std::for_each(players.begin(),players.end(),[this](Player p){
        this->update_player_in_db(p.get_server_id(),p.get_score(),
          QString(this->get_win_from_int(static_cast<int>(p.get_state())).c_str()),p.get_mise());
    });


}
void game_handler::disconnecte_player(player_thread *t)
{
    auto p_it= player_threads.begin();
    for(auto it=player_threads.begin();it!=player_threads.end();it++)
    {
        if(*it==t)
        {
            p_it=it;
        }
    }
    player_threads.erase(p_it);
    bj_game.remove_player(t->get_db_id());
    if(player_threads.empty())
    {

    }
}
void game_handler::update_player_in_db(int id_player, int score, QString status, int amount)
{
    qDebug()<<status;
this->connexion.insert_player_score(this->bj_game.get_game_id(),id_player,score,status, amount);
}
std::string game_handler::get_win_from_int(int a){
    switch (a){
    case 1:{
        return "WIN";
        break;
    }
    case 2:{
        return "LOOSE";
        break;
    }
    case 4:{
        return "STRIKE";
        break;
    }
    case 5:{
        return "DRAW";
        break;
    }
    default :return "";
    }
}
