#include <string>
#include <sstream>
#include <iostream>

#include "creategamewidget.h"
#include "ui_creategamewidget.h"
#include "../common/lobby_command.h"


#define MAX_PLAYERS 2

createGameWidget::createGameWidget(BlockingQueue<std::string> &send,
                                   BlockingQueue<std::string> &recv,
                                   QWidget *parent) :
    QWidget(parent),
    ui(new Ui::createGameWidget),
    to_send_queue(send),
    to_recv_queue(recv)
{
    ui->setupUi(this);
}

createGameWidget::~createGameWidget()
{
    delete ui;
}

void createGameWidget::on_goBack_clicked()
{
    emit goHomeClicked();
}


void createGameWidget::on_startGame_clicked()
{
    std::stringstream payload;

    payload << ui->numPlayers->value();
    payload << " ";
    payload << ui->gameName->text().toStdString();

    std::cout << "SENT: " << payload.str() << std::endl;
    LobbyCommand cmd(CREATE_CODE, payload.str());

    std::string cmd_ser = cmd.serialize();
    to_send_queue.push(cmd_ser);

    LobbyCommand rsp(to_recv_queue.pop());
    std::cout << "RESPONSE: " << rsp.get_code() << std::endl;


    if (rsp.get_code() == COMMAND_SUCCESS_CODE) {
        emit exit();
    }
}

