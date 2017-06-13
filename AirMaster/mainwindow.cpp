#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initWindow();
    on_pushButton_cool_clicked();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWindow()
{
    airMaster=new AirConditionMaster();
    PacketHandler* packHandler=new PacketHandler(*airMaster);
    ResQueueHandler* queueHandler=new ResQueueHandler(nullptr,packHandler);
    resQueueHelper=new ReQueueHelper(nullptr,queueHandler);


}

void MainWindow::on_pushButton_up_clicked()
{
    int windTemp=ui->lcdNumber->value();
    windTemp++;
    ui->lcdNumber->display(windTemp);
    if(windTemp==upperBound)
        ui->pushButton_up->setEnabled(false);
    else
        ui->pushButton_up->setEnabled(true);
}

void MainWindow::on_pushButton_down_clicked()
{
    int windTemp=ui->lcdNumber->value();
    windTemp--;
    ui->lcdNumber->display(windTemp);
    if(windTemp==lowerBound)
        ui->pushButton_down->setEnabled(false);
    else
        ui->pushButton_down->setEnabled(true);
}

void MainWindow::on_pushButton_cool_clicked()
{
    ui->lcdNumber->display(22);
    ui->pushButton_up->setEnabled(true);
    ui->pushButton_down->setEnabled(true);
    ui->pushButton_heat->setEnabled(true);
    ui->pushButton_cool->setEnabled(false);
    ui->label_mode->setText("COOLER");
    ui->label_mode->setStyleSheet("color:lightblue;font-weight:bold");
    lowerBound=14;
    upperBound=23;
}

void MainWindow::on_pushButton_heat_clicked()
{
    ui->lcdNumber->display(28);
    ui->pushButton_up->setEnabled(true);
    ui->pushButton_down->setEnabled(true);
    ui->pushButton_heat->setEnabled(false);
    ui->pushButton_cool->setEnabled(true);
    ui->label_mode->setText("HEATER");
    ui->label_mode->setStyleSheet("color:red;font-weight:bold");
    lowerBound=27;
    upperBound=35;
}

void MainWindow::on_pushButton_set_clicked()
{
    int rate=ui->spinBox_period->value();
    airMaster->setFreshperiod(rate);
    if(ui->pushButton_cool->isEnabled())
        airMaster->setCurrentModeStr("HOT");
    else
        airMaster->setCurrentModeStr("COLD");
    int windTemp=ui->lcdNumber->value();
    airMaster->setDefaTemperature(windTemp);

    //A Certain Package should be sent here*

}
