#include "db_connexion.h"

db_connexion::db_connexion(){
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
    if(db.open())
    {
        is_open=true;
        this->query=QSqlQuery(db);
        this->query.exec("create table game "
                         "(gameID INTEGER NOT NULL,"
                         "PRIMARY KEY(gameID AUTOINCREMENT)) ");
        this->query.exec("create table game_players_scores "
                         "(id_game INTEGER NOT NULL, id_player INTEGER NOT NULL,"
                         "score REAL, status TEXT, amount REAL,"
                         "FOREIGN KEY(id_player) REFERENCES player,"
                         "FOREIGN KEY(id_game) REFERENCES game(gameID),"
                         "PRIMARY KEY(id_game,id_player))");
        this->query.exec("create table player "
                         "(id_player INTEGER NOT NULL, nickname TEXT NOT NULL UNIQUE,"
                         "amount	REAL NOT NULL DEFAULT 500,"
                         "CONSTRAINT amountnotnull CHECK(amount>=0),"
                         "PRIMARY KEY(id_player AUTOINCREMENT) )");
        this->query.exec("create table sqlite_sequence "
                         "(name ,"
                         "seq)");
    }
}

bool db_connexion::db_is_open()
{
    return is_open;
}
void db_connexion::checkUser (QString name, user_info &info ){
    db.open();
    query= QSqlQuery(db);
    query.exec("SELECT * FROM player WHERE nickname ='"+name+"'");
        qDebug()<<"Query exec...\n";
        if (query.next()){
            int id = query.value(0).toInt();
            QString nickname = query.value(1).toString();
            int amount = query.value(2).toInt();
            info= user_info(nickname,id,amount);
            qDebug()<<"no next\n";
        }else{
            query.exec("INSERT INTO player (nickname,amount) VALUES ('"
                             + name +"','"+ QString::number(500) +"')");
            query.exec("SELECT * FROM player WHERE nickname ='"+name+"'");
            query.next();
            int id = query.value(0).toInt();
            QString nickname = query.value(1).toString();
            int amount = query.value(2).toInt();
            info= user_info(nickname,id,amount);
            db.commit();

            qDebug()<<"chek else\n";
        }


}


void db_connexion:: read_Db(user_info& info){
    if (query.next()){
        int id = query.value("id").toInt();
        QString nickname = query.value("nickname").toString();
        int amount = query.value("amount").toInt();
        info= user_info(nickname,id,amount);
    }else{
        qDebug()<<"no next\n";

    }
}


void db_connexion::clear_query(){
    query.clear();
    qDebug()<<query.isActive()<<"\n";
}

void db_connexion::update_bank_player(int id_player,int mount)
{
    this->query.exec("UPDATE player SET amount = ("+ QString::number(mount) +
                     ") WHERE id_player =  "+ QString::number(id_player) +"");
}

void db_connexion::insert_player_score(int id_game, int id_player,int score ,QString status,int mount )
{
    this->query.exec("INSERT INTO game_players_scores (id_game,id_player,score,status,amount) "
                     "VALUES(" + QString::number(id_game) +","+ QString::number(id_player) +","
                     +QString::number(score)+",'"+status+"',"+QString::number(mount)+")");
    db.commit();
}


int db_connexion::insert_get_game_id()
{
    this->query.exec("INSERT INTO game (gameID) VALUES(NULL);");
    this->query.exec("SELECT max(gameID) FROM game;");
    query.next();
    int gameid = query.value(0).toInt();
    return gameid;
}
