#ifndef PLAYER_THREAD_H
#define PLAYER_THREAD_H
#include "QThread"
#include "QTcpSocket"
#include "bj_packet_ip/json_packet.h"
#include "bj_json/json_gen.h"
#include "bj_json/json_interpreter.h"
class game_handler;
class player_thread : public QThread
{
    Q_OBJECT
    QTcpSocket *player_socket_;
    qintptr socket_descriptor_;
    int player_game_id;
    std::string userName;
    size_t db_id;
    size_t bank;
    game_handler* handler_;

    json_packet packet;
    json_interpreter inperpreter;
    json_gen json_generator;
    QByteArray buffer;

    /**
 * @brief handle_received processes the messages
 * @param type
 */
    void handle_received(QString,Action_Send type);
public:
    /**
 * @brief set_handler setter of handler
 */
    void set_handler(game_handler*);

protected:
    /**
  * @brief run create  a socket for player
  */
    void  run() override;

private slots:
    void read_in();
    /**
  * @brief log_out clear socket
  */
    void log_out();
public:
    /**
    * @brief writeData write information on player in a json file
    * @param g game
    */
    void writeData(Game g);
    bool operator==(const player_thread*t){ return this->db_id==t->db_id;}
    int get_db_id(){return db_id;}

    /**
  * @brief player_thread generate information in json
  * @param socket
  */
    explicit player_thread(QTcpSocket* socket);
    /**
  * @brief player_thread  generate information in json
  * @param socket_descriptor
  * @param parent
  */
    explicit player_thread(qintptr socket_descriptor, QObject* parent=0);

signals:
    void error(QTcpSocket::SocketError error);

};

#endif // PLAYER_THREAD_H
