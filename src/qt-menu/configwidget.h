#ifndef CONFIGWIDGET_H
#define CONFIGWIDGET_H

#include <QWidget>

namespace Ui {
class configWidget;
}

class configWidget : public QWidget
{
    Q_OBJECT

public:
    explicit configWidget(QWidget *parent = nullptr);
    ~configWidget();

private:
    Ui::configWidget *ui;
};

#endif // CONFIGWIDGET_H
