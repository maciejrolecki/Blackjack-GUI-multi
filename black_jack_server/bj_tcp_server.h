#ifndef BJ_TCP_SERVER_H
#define BJ_TCP_SERVER_H
#include "QTcpServer"
#include "vector"
#include "game_handler.h"
#include "QDebug"
#define PORT 2021
class bj_tcp_server : public QTcpServer
{
    Q_OBJECT
    std::vector<game_handler> game_handlers;
private:
    /**
     * @brief initialise_game intialise the game , create a thred for player.
     */
    void initialise_game(qintptr&);


protected:
    /**
   * @brief incomingConnection
   * @param handle
   */
  void  incomingConnection(qintptr handle) override;
public:
  /**
     * @brief bj_tcp_server
     * @param parent
     */
    explicit  bj_tcp_server(QObject*parent=0);
  /**
     * @brief start_server launch the server
     *  the server need a port and QhostAdress
     *  if the server start we have a message server connected
     */
    void start_server();
};

#endif // BJ_TCP_SERVER_H
