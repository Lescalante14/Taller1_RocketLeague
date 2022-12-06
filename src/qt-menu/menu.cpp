#include "menu.h"
#include "./ui_menu.h"

#define HOME 0
#define CREATE_GAME 1
#define JOIN_GAME 2
#define CONFIG 3
#define ABOUT 4

Menu::Menu(bool *play,
           BlockingQueue<std::string> &send,
           BlockingQueue<std::string> &recv,
           QWidget *parent)

    : QMainWindow(parent),
      ui(new Ui::Menu),
      _play(play),
      c_widg(send, recv),
      j_widg(send, recv)
{
    ui->setupUi(this);
    ui->stackedWidget->insertWidget(CREATE_GAME, &c_widg);
    ui->stackedWidget->insertWidget(JOIN_GAME, &j_widg);

    connect(&c_widg, SIGNAL(goHomeClicked()), this, SLOT(goHome()));
    connect(&j_widg, SIGNAL(goHomeClicked()), this, SLOT(goHome()));

    connect(&c_widg, SIGNAL(exit()), this, SLOT(play()));
    connect(&j_widg, SIGNAL(exit()), this, SLOT(play()));
}

Menu::~Menu()
{
    delete ui;
}

void Menu::play() {
    if (this->_play) {
        *this->_play = true;
    }
    this->close();
}

void Menu::goHome() {
    ui->stackedWidget->setCurrentIndex(HOME);
}

void Menu::on_createButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(CREATE_GAME);
}

void Menu::on_joinButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(JOIN_GAME);
    this->j_widg.updateGameList();
}

