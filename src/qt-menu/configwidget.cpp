#include <yaml-cpp/yaml.h>

#include "configwidget.h"
#include "ui_configwidget.h"


configWidget::configWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::configWidget)
{
    ui->setupUi(this);
}

configWidget::~configWidget()
{
    delete ui;
}

void configWidget::on_comboBox_currentIndexChanged(int index)
{
    YAML::Node config = YAML::LoadFile("/etc/rocket_league/.rl_config.yml");
    config["ball_size"] = index;
}


void configWidget::on_dial_sliderMoved(int position)
{
    YAML::Node config = YAML::LoadFile("/etc/rocket_league/.rl_config.yml");
    config["match_duration"] = index;
}

