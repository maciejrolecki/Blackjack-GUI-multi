#include "client_connection_window.h"
#include "ui_client_connection_window.h"
#include "controller.h"

client_connection_window::client_connection_window(Controller* controller, QWidget *parent)
    : QWidget(parent), ui(new Ui::client_connection_window),controller(controller)
{
    ui->setupUi(this);
}

client_connection_window::~client_connection_window()
{
    delete ui;
}

void client_connection_window::on__sendBt_clicked()
{
controller->conection_serv(ui->textEdit_2->toPlainText());
}


void client_connection_window::set_controller(Controller* controller){
    this->controller= controller;
}

