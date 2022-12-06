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

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_dial_sliderMoved(int position);

private:
    Ui::configWidget *ui;
};

#endif // CONFIGWIDGET_H
