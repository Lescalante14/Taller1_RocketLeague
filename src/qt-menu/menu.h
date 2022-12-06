#ifndef MENU_H
#define MENU_H

#include <QMainWindow>

#include "creategamewidget.h"
#include "joingamewidget.h"
#include "configwidget.h"

#include "../common/blocking_queue.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Menu; }
QT_END_NAMESPACE

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    Menu(bool *play,
         BlockingQueue<std::string> &send,
         BlockingQueue<std::string> &recv,
         QWidget *parent = nullptr);

    ~Menu();

private slots:
    void goHome();
    void play();
    void on_createButton_clicked();
    void on_joinButton_clicked();

    void on_configButton_clicked();

private:
    Ui::Menu *ui;
    bool *_play = nullptr;
    createGameWidget c_widg;
    joinGameWidget j_widg;
    configWidget conf_widg;
};
#endif // MENU_H
