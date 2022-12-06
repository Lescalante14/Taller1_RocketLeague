#ifndef CREATEGAMEWIDGET_H
#define CREATEGAMEWIDGET_H

#include <QWidget>

#include "../common/blocking_queue.h"

namespace Ui {
class createGameWidget;
}

class createGameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit createGameWidget(BlockingQueue<std::string> &send,
                              BlockingQueue<std::string> &recv,
                              QWidget *parent = nullptr);
    ~createGameWidget();

private slots:
    void on_goBack_clicked();


    void on_startGame_clicked();

private:
    Ui::createGameWidget *ui;
    BlockingQueue<std::string> &to_send_queue;
    BlockingQueue<std::string> &to_recv_queue;

signals:
    void goHomeClicked();
    void exit();

};

#endif // CREATEGAMEWIDGET_H
