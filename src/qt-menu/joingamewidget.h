#ifndef JOINGAMEWIDGET_H
#define JOINGAMEWIDGET_H

#include <QWidget>
#include <QListWidget>

#include "../common/blocking_queue.h"

namespace Ui {
class joinGameWidget;
}

class joinGameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit joinGameWidget(BlockingQueue<std::string> &send,
                            BlockingQueue<std::string> &recv,
                            QWidget *parent = nullptr);
    void updateGameList();
    ~joinGameWidget();

private slots:
    void on_goBack_clicked();

    void on_joinButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_refreshButton_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::joinGameWidget *ui;
    BlockingQueue<std::string> &to_send_queue;
    BlockingQueue<std::string> &to_recv_queue;
    std::string selectedGame;



signals:
    void goHomeClicked();
    void exit();
};

#endif // JOINGAMEWIDGET_H
