#ifndef CLIENT_CONNECTION_WINDOW_H
#define CLIENT_CONNECTION_WINDOW_H

#include <QWidget>
#include "bj_json/game_info.h"



QT_BEGIN_NAMESPACE
namespace Ui { class client_connection_window; }
QT_END_NAMESPACE

class Controller;

class client_connection_window : public QWidget
{
    Q_OBJECT

public:
    /**
     * constructor of the view for the connection
     * @brief client_connection_window
     * @param controller
     * @param parent
     */
    client_connection_window(Controller* controller,QWidget *parent = nullptr);
    /**
     * destructor
     * @brief ~client_connection_window
     */
     ~client_connection_window();
    /**
     * setter of the controller
     * @brief set_controller
     * @param controller
     */
    void set_controller(Controller* controller);

private slots:
    /**
     * action of the button sendBt when he is clicked
     * @brief on__sendBt_clicked
     */
    void on__sendBt_clicked();

private:
    /**
     * @brief ui
     */
    Ui::client_connection_window *ui;
    /**
     * @brief controller
     */
    Controller* controller;
};

#endif // CLIENT_CONNECTION_WINDOW_H
