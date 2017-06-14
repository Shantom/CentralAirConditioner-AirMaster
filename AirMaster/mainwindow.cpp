#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initWindow();
    timer.setInterval(300);
    connect(&timer,&QTimer::timeout,this,&MainWindow::refreshTable);
    timer.start();
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
    resQueueHelper->sendMasterInfo();
}

void MainWindow::refreshTable()
{
    QString oldID="";

    auto oldItem=ui->tableWidget->currentItem();
    if(oldItem)
    {
        int curRow=oldItem->row();
        auto oldItem=ui->tableWidget->item(curRow,0);
        oldID=oldItem->text();
    }


    auto servants=resQueueHelper->getAllServantsStatus();
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    int rowCount=ui->tableWidget->rowCount();
    for(int i=0;i<rowCount;i++)
    {
        ui->tableWidget->removeRow(0);
    }
    ui->tableWidget->setSortingEnabled(false);

    int nOldRowCount = ui->tableWidget->rowCount();

    for(auto servantPair:servants)
    {
        ServantStatus *servant=servantPair.second;
        ui->tableWidget->insertRow(nOldRowCount);

        QString RoomID=servant->room.c_str();
        QTableWidgetItem *IRoomID = new QTableWidgetItem(RoomID);
        ui->tableWidget->setItem(nOldRowCount, 0, IRoomID);
        IRoomID->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

        QString Temperature=QString::number(servant->currentTemperature);
        QTableWidgetItem *ITemperature = new QTableWidgetItem(Temperature);
        ui->tableWidget->setItem(nOldRowCount, 1, ITemperature);
        ITemperature->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

        QString Working=servant->working?"Yes":"No";
        QTableWidgetItem *IWorking = new QTableWidgetItem(Working);
        ui->tableWidget->setItem(nOldRowCount, 2, IWorking);
        IWorking->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

        QString Velocity=servant->velocity.c_str();
        QTableWidgetItem *IVelocity = new QTableWidgetItem(Velocity);
        ui->tableWidget->setItem(nOldRowCount, 3, IVelocity);
        IVelocity->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

    }
    ui->tableWidget->setSortingEnabled(true);
    ui->tableWidget->sortByColumn(0, Qt::AscendingOrder);

    auto oldItems=ui->tableWidget->findItems(oldID,Qt::MatchExactly);
    if(!oldItems.empty())
    {
        ui->tableWidget->setCurrentItem(oldItems[0]);
    }
}
