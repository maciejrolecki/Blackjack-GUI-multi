#include "client_connection_window.h"

#include <QApplication>
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller* controller = new Controller();
    controller->start();
    return a.exec();
}
