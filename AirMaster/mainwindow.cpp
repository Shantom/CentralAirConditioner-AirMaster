#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initWindow();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loginAdmin()
{
    LoginAirMaster loginer;
    loginer.showSignInWindow();
}

void MainWindow::initWindow()
{
    airMaster=new AirConditionMaster();
    PacketHandler* packHandler=new PacketHandler(*airMaster);
    ResQueueHandler* queueHandler=new ResQueueHandler(nullptr,packHandler);
    resQueueHelper=new ReQueueHelper(nullptr,queueHandler);


}
