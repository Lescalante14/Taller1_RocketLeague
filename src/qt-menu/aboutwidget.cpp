#include "aboutwidget.h"
#include "ui_aboutwidget.h"

aboutWidget::aboutWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::aboutWidget)
{
    ui->setupUi(this);
}

aboutWidget::~aboutWidget()
{
    delete ui;
}

void aboutWidget::on_goBack_clicked()
{

    emit goHome();
}

