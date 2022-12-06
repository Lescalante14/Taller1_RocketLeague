#ifndef ABOUTWIDGET_H
#define ABOUTWIDGET_H

#include <QWidget>

namespace Ui {
class aboutWidget;
}

class aboutWidget : public QWidget
{
    Q_OBJECT

public:
    explicit aboutWidget(QWidget *parent = nullptr);
    ~aboutWidget();

private slots:
    void on_goBack_clicked();

private:
    Ui::aboutWidget *ui;

signals:

    void goHome();

};

#endif // ABOUTWIDGET_H
