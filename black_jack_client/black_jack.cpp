#include "black_jack.h"
#include "ui_black_jack.h"
#include "controller.h"

//#include de la libraire

black_jack::black_jack(Controller* controller, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::black_jack),controller(controller)
{
    ui->setupUi(this);
}

black_jack::~black_jack()
{
    delete ui;
}

void black_jack::on_drawBtn_clicked()
{
    controller->button_draw();
}

void black_jack::on_stayBtn_clicked()
{
    controller->button_stay();
}


void black_jack::on_ButtonAdd_clicked()
{
    controller->button_bet(ui->betAmountText->value());
}


void black_jack::set_controller(Controller* controller){
    this->controller= controller;
}


void black_jack::apply_game_info(){
    reset_view();
    game_info game = controller->get_game_info();
    int a = 0;
    ui->croupierCards->setHorizontalSpacing(0);
    if(!game.get_info().empty()){
        for(int i = 0;i<game.get_nb_players();i++){
            auto player_name= return_correct_player_name_object(i);
            player_name->setText(game.get_info().at(i).get_name().c_str());
            if(i==controller->get_player_game_id())
                player_name->setStyleSheet("QLabel { background-color : red; color : blue; }");
        }
        if(!game.get_croupier_cards().empty()){
            for ( auto card : game.get_croupier_cards()) {
                QLabel  *label  = new  QLabel();
                QPixmap pixmap = QPixmap(QString::fromUtf8(":/ressources/cards/"+card+".png"));
                pixmap = pixmap.scaled(50,70 );
                label->setPixmap(pixmap);
                ui->croupierCards->addWidget(label,0,a);
                a++;
            }
            if(a==1){
                QLabel  *label  = new QLabel();
                QPixmap pixmap = QPixmap(QString::fromUtf8(":/ressources/cards/back.png"));
                pixmap = pixmap.scaled(50,70 );
                label->setPixmap(pixmap);
                ui->croupierCards->addWidget(label,0,a);
            }
            a=0;
            for(int i = 0;i<game.get_nb_players();i++){
                auto player_cards= return_correct_player_cards_object(i);
                player_cards->setHorizontalSpacing(0);
                auto playerCards = game.get_info().at(i).get_cards();
                for ( auto card : playerCards ) {
                    QLabel  *label  = new QLabel();
                    QPixmap pixmap = QPixmap(QString::fromUtf8(":/ressources/cards/"+card+".png"));
                    pixmap = pixmap.scaled(50,70 );
                    label->setPixmap(pixmap);
                    player_cards->addWidget(label,0,a);
                    a++;

                }
                a=0;
            }
        }
    }
    ui->valueBankLabel->setText(QString::number(game.get_info().at(controller->get_player_game_id()).get_bank()));
        ui->valueBet->setText(QString::number(game.get_info().at(controller->get_player_game_id()).get_mise()));

    switch(game.get_game_state().toInt()){
    case 1:{
        qDebug()<<controller->get_player_game_id();
          qDebug()<<game.get_current_player();
        if(controller->get_player_game_id()==game.get_current_player()){
            ui->comm_lab->setText("Please choose wether to stay or hit");
            ui->drawBtn->setEnabled(true);
            ui->stayBtn->setEnabled(true);
        }else{
            ui->comm_lab->setText("Please wait for you turn");
            ui->drawBtn->setEnabled(false);
            ui->stayBtn->setEnabled(false);
        }
        ui->ButtonAdd->setEnabled(false);
        ui->betAmountText->setEnabled(false);

        break;
    }
    case 0:{
        if(game.get_info().at(controller->get_player_game_id()).get_state()==6){
            ui->comm_lab->setText("Type in the amount you'd like to bet");
            ui->ButtonAdd->setEnabled(true);
            ui->betAmountText->setEnabled(true);
        }else{
            ui->comm_lab->setText("Please wait for the other players");
            ui->drawBtn->setEnabled(false);
            ui->stayBtn->setEnabled(false);
            ui->ButtonAdd->setEnabled(false);
        }
        ui->drawBtn->setEnabled(false);
        ui->stayBtn->setEnabled(false);
        break;
    }
    case 2:{
        ui->comm_lab->setText(get_win_from_int(game.get_info().at(controller->get_player_game_id()).get_state()).c_str());
        ui->drawBtn->setEnabled(false);
        ui->stayBtn->setEnabled(false);
        ui->ButtonAdd->setEnabled(false);
        ui->betAmountText->setEnabled(false);
        break;
    }
    default:{
        break;
    }

        //mettre à jour le label et le fait si les boutons sont click

    }
}

QGridLayout* black_jack::return_correct_player_cards_object(int i){
    switch (i){
    case 0 : return ui->jCards1;
    case 1 : return ui->jCards2;
    case 2 : return ui->jCards3;
    case 3 : return ui->jCards4;
    case 4 : return ui->jCards5;
    case 5 : return ui->jCards6;
    case 6 : return ui->jCards7;
    default: return nullptr;
    }
}
QLabel * black_jack::return_correct_player_name_object(int i){
    switch (i){
    case 0 : return ui->jName1;
    case 1 : return ui->jName2;
    case 2 : return ui->jName3;
    case 3 : return ui->jName4;
    case 4 : return ui->jName5;
    case 5 : return ui->jName6;
    case 6 : return ui->jName7;
    default: return nullptr;
    }
}

void black_jack::reset_view(){
    while (!ui->croupierCards->isEmpty()){
        auto* item = ui->croupierCards->itemAt(0);
        //ui->croupierCards->removeItem(item);
        delete item->widget();
    }
    for(int i = 0;i<7;i++){
        auto * player_cards = return_correct_player_cards_object(i);
        while (!player_cards->isEmpty()){
            auto* item = player_cards->itemAt(0);
           // player_cards->removeItem(item);

            delete item->widget();
        }
        auto player_name = return_correct_player_name_object(i);
        player_name->setText("");
    }
    ui->valueBankLabel->setText("");
    ui->comm_lab->setText("");
}

std::string black_jack::get_win_from_int(int a){
    switch (a){
    case 1:{
        return "You won!!";
        break;
    }
    case 2:{
        return "You just lost!?";
        break;
    }
    case 4:{
        return "yo, 21, just like that";
        break;
    }
    case 5:{
        return "no luck, a draw";
        break;
    }
    default :return "";
    }
}
