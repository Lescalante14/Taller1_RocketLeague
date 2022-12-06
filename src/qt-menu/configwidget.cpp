#include <yaml-cpp/yaml.h>
#include <iostream>
#include <fstream>

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
    std::ofstream fout("/etc/rocket_league/.rl_config.yml");
    fout << config;
    std::cout << "SAVED\n";
}


void configWidget::on_dial_sliderMoved(int position)
{
    YAML::Node config = YAML::LoadFile("/etc/rocket_league/.rl_config.yml");
    config["match_duration"] = position;
    std::ofstream fout("/etc/rocket_league/.rl_config.yml");
    fout << config;

    QString pos = QString::fromStdString(std::to_string(position) + " sec");
    ui->durationLabel->setText(pos);
}

