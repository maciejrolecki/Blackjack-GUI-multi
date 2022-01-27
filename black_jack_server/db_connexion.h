#ifndef DB_CONNEXION_H
#define DB_CONNEXION_H
#include <iostream>

#define q2c(string) string.toStdString()
#include <QtSql>
//#include "bj_query.h"
struct user_info {
    QString nickname;
    int id_;
    int  amount_;
    int player_game_id=0;

public:
    /**
     * @brief Default constructor
     * */
    user_info()=default;


    user_info(QString nckname ,int id ,int amount ): nickname(nckname),id_(id),amount_(amount){}
    /**
   * @brief get_nickname getter of nickname
   * @return nickname of player
   */
    inline QString get_nickname(){return nickname;}

    /**
   * @brief get_amount getter of amount
   * @return amount on player
   */
    inline int get_amount(){return amount_;}

};


class db_connexion
{
    QSqlDatabase db;
    QSqlQuery query;
    bool is_open;
public:
    /**
       * @brief Default constructor
       *
       * */
    db_connexion();
    /**
     * @brief open_db open the daba
     */
    void open_db();
    /**
     * @brief db_is_open check is the db is open
     * @return bool true if the db_is_open
     */
    bool db_is_open();
    /**
     * @brief checkUser check if the user is in the db , is the user
     * is not in the db , we create inforamtion of user in db
     */
    void checkUser(QString, user_info&);
    /**
     * @brief read_Db read information in the db
     */
    void read_Db(user_info&);
    /**
     * @brief clear_query clear the query
     */
    void clear_query();
    /**
     * @brief update in the database the player's bank amount in parameter
     *  by increasing with the mount in parameter
     */
    void update_bank_player(int id_player,int mount);
    /**
     * @brief update in the database the player's bank amount in parameter
     * by decreasing with the mount in parameter
     */
    void update_min_amount_player(int id_player,int mount);
    /**
     * @brief updates the player's stake in the database based on the gameid
     * and player id and displays the game status
     */
    void insert_player_score(int,int,int,QString,int);
    /**
    * @brief updates and retrieves the part number in the database
    * @return integer of gameID
    */
    int insert_get_game_id();
};

#endif // DB_CONNEXION_H
