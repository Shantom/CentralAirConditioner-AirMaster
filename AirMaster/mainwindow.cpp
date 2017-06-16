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
    ui->pushButton_down->setEnabled(true);
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
    ui->pushButton_up->setEnabled(true);
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
    lowerBound=18;
    upperBound=25;
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
    lowerBound=25;
    upperBound=30;
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
    resQueueHelper->sendWorkingState();
    resQueueHelper->sendFreshPeroid();
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

    AirFee* allFee = resQueueHelper->getResQueueHandler()->getAirFeer();
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
        addItemToRow(nOldRowCount,0,RoomID);

        int temp=servant->currentTemperature;
        QString Temperature="N/A";
        if(temp!=-999)
            Temperature=QString::number(temp);
        addItemToRow(nOldRowCount,1,Temperature);

        QString Working=servant->working?"Yes":"No";
        addItemToRow(nOldRowCount,2,Working);

        QString Velocity=servant->velocity.c_str();
        addItemToRow(nOldRowCount,3, Velocity);


        auto pRoom=allFee->getRoomFee(servant->room);
        QString fee="0";
        QString kwh="0";
        if(pRoom)
        {
            fee = QString::number(pRoom->fee);
            kwh = QString::number(pRoom->KWH);
        }
        addItemToRow(nOldRowCount,4,fee);
        addItemToRow(nOldRowCount,5,kwh);


    }
    ui->tableWidget->setSortingEnabled(true);
    ui->tableWidget->sortByColumn(0, Qt::AscendingOrder);

    auto oldItems=ui->tableWidget->findItems(oldID,Qt::MatchExactly);
    if(!oldItems.empty())
    {
        ui->tableWidget->setCurrentItem(oldItems[0]);
    }
}

void MainWindow::addItemToRow(int nOldRow, int numth, QString item)
{
    QTableWidgetItem *itemWidget= new QTableWidgetItem(item);
    ui->tableWidget->setItem(nOldRow, numth, itemWidget);
    itemWidget->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
}

void MainWindow::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    QString RoomID=ui->tableWidget->item(row,0)->text();
    AiReportSystem* reportSys=resQueueHelper->getResQueueHandler()->getAirReportor();
    auto resquests=reportSys->getAllCompleteRequests();
    int time=reportSys->getSwitchTime(RoomID.toStdString());
    rw.setRoom(RoomID,time,resquests);
    rw.show();
}

void MainWindow::on_pushButton_clicked()
{
    rw.setRoom(QString(""),0,&blank);
    rw.show();

}
