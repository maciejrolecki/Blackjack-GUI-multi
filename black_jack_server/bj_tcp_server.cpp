#include "bj_tcp_server.h"
bj_tcp_server::bj_tcp_server(QObject*parent): QTcpServer(parent){}

void bj_tcp_server::start_server()
{
    if(this->listen(QHostAddress("localhost"),PORT))
    {
        qDebug()<< "-----------------------------------\n" <<"Server online...\n"<<"-----------------------------------\n";

    }else
    {
        qDebug()<<"Server not connectect error...\n";
    }
}
void  bj_tcp_server::incomingConnection(qintptr handle)
{
       qDebug()<<"---------------------------------------\n"<< "New client coming with socket id"<<handle<<"----------------------------------------------\n";
    if(this->game_handlers.empty())
    {
        qDebug()<<"Game handler empty creating new one...\n";
        initialise_game(handle);
    }else
    {
        bool added=false;
        for(game_handler h : game_handlers){
            if(!h.server_is_Full())
            {
                added=true;
                h.creat_player_thread(handle);
                h.start_last_thread();
                break;
            }
        }
        if(!added)
        {
            initialise_game(handle);
        }
    }
}

void  bj_tcp_server::initialise_game(qintptr& handle){
    game_handlers.push_back(game_handler(this));
    game_handlers.back().creat_player_thread(handle);
    game_handlers.back().start_last_thread();
}
