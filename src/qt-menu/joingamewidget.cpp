#include <string>
#include <sstream>
#include <iostream>

#include "joingamewidget.h"
#include "ui_joingamewidget.h"
#include "../common/lobby_command.h"

joinGameWidget::joinGameWidget(BlockingQueue<std::string> &send,
                               BlockingQueue<std::string> &recv,
                               QWidget *parent) :
    QWidget(parent),
    ui(new Ui::joinGameWidget),
    to_send_queue(send),
    to_recv_queue(recv)
{
    ui->setupUi(this);
    this->updateGameList();
}

joinGameWidget::~joinGameWidget()
{
    delete ui;
}

void joinGameWidget::updateGameList()
{
    ui->listWidget->clear();
    LobbyCommand cmd(LIST_CODE, std::string());

    std::string cmd_ser = cmd.serialize();
    this->to_send_queue.push(cmd_ser);

    LobbyCommand rsp(this->to_recv_queue.pop());
    std::stringstream rsp_ss(rsp.get_payload());

    for (std::string g; std::getline(rsp_ss, g);) {
        std::stringstream ss(g);
        std::string name;
        std::string joined;
        std::string max_p;

        ss >> joined;
        ss >> max_p;
        ss >> name;
        QString fmtGame = QString::fromStdString(name + " (" + joined + "/" + max_p + ")");
        ui->listWidget->addItem(fmtGame);
    }
}

void joinGameWidget::on_goBack_clicked()
{
    emit goHomeClicked();
}


void joinGameWidget::on_joinButton_clicked()
{
    if (!this->selectedGame.size()) {
        std::cout << "NONE\n";
        return;
    }
    LobbyCommand cmd(JOIN_CODE, this->selectedGame);

    std::string cmd_ser = cmd.serialize();
    this->to_send_queue.push(cmd_ser);
    std::cout << "SENT: " << this->selectedGame << std::endl;

    LobbyCommand rsp(to_recv_queue.pop());
    std::cout << "RESPONSE: " << rsp.get_code() << std::endl;

    if (rsp.get_code() == COMMAND_SUCCESS_CODE) {
        emit exit();
    }
}


void joinGameWidget::on_listWidget_itemClicked(QListWidgetItem *item)
{
    std::stringstream ss(item->text().toStdString());
    this->selectedGame = "";
    ss >> this->selectedGame;
}


void joinGameWidget::on_refreshButton_clicked()
{
    this->updateGameList();
}


void joinGameWidget::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    this->on_joinButton_clicked();
}

