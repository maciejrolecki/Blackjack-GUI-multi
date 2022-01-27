#include <QCoreApplication>
#include "Model/Game.h"
#include "bj_json/json_gen.h"
#include "bj_tcp_server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
  bj_tcp_server server;
  server.start_server();
    return a.exec();
}
