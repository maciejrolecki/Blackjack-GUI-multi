#ifndef BLACK_JACK_H
#define BLACK_JACK_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include "Model/Card.h"
#include "Model/Game.h"



QT_BEGIN_NAMESPACE
namespace Ui { class black_jack; }
QT_END_NAMESPACE

class Controller;

class black_jack : public QWidget
{
    Q_OBJECT

public:
    /**
     * constructor of the view
     * @brief black_jack
     * @param controller
     * @param parent
     */
    black_jack(Controller* controller,QWidget *parent = nullptr);
    ~black_jack();

    /**
     * setter for the controller
     * @brief set_controller
     * @param controller
     */
    void set_controller(Controller* controller);

    /**
     * apply the differents changes
     * @brief apply_game_info
     */
    void apply_game_info();

    /**
     * remove all the card from the player and the croupier
     * @brief reset_view
     */
    void reset_view();

    /**
     * return the cards of the players
     * @brief return_correct_player_cards_object
     * @param i
     * @return card
     */
    QGridLayout * return_correct_player_cards_object(int i);

    /**
     * return the name of the differents players
     * @brief return_correct_player_name_object
     * @param i
     * @return name
     */
    QLabel * return_correct_player_name_object(int i);

    /**
     * Returns the correct text according to the player's statu at the end of a game.
     */
    std::string get_win_from_int(int a);


private slots:
    /**
     * define the action of the button draw when you clicked
     * @brief on_drawBtn_clicked
     */
    void on_drawBtn_clicked();
    /**
     * define the action of the button stay when you clicked
     * @brief on_stayBtn_clicked
     */
    void on_stayBtn_clicked();

    /**
     *define the action of the button add when you clicked
     * @brief on_ButtonAdd_clicked
     */
    void on_ButtonAdd_clicked();

private:
    /**
     * pointeur ui
     * @brief ui
     */
    Ui::black_jack *ui;
    /**
     * pointeur controller
     * @brief controller
     */
    Controller* controller;
};
#endif // BLACK_JACK_H
