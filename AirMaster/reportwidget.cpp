#include "reportwidget.h"
#include "ui_reportwidget.h"

ReportWidget::ReportWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReportWidget)
{
    ui->setupUi(this);
    allCompleteRequests=nullptr;
    timer.setInterval(1000);
    connect(&timer,&QTimer::timeout,this,&ReportWidget::refreshTable);
    timer.start();

    ui->tableWidget->setColumnWidth(0,170);
    ui->tableWidget->setColumnWidth(1,170);
    ui->tableWidget->setColumnWidth(2,80);
    ui->tableWidget->setColumnWidth(3,80);
    ui->tableWidget->setColumnWidth(4,80);
    ui->tableWidget->setColumnWidth(5,30);

}

void ReportWidget::setRoom(QString RoomID, std::map<std::__cxx11::string, std::vector<pRequestInfo> > *allCompleteRequests)
{
    this->RoomID=RoomID;
    ui->label_roomid->setText(RoomID);
    this->allCompleteRequests=allCompleteRequests;
    refreshTable();
}

ReportWidget::~ReportWidget()
{
    delete ui;
}

void ReportWidget::refreshTable()
{
    if(!allCompleteRequests)
        return;

    QString oldID="";

    auto oldItem=ui->tableWidget->currentItem();
    if(oldItem)
    {
        int curRow=oldItem->row();
        auto oldItem=ui->tableWidget->item(curRow,0);
        oldID=oldItem->text();
    }


    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    //clear the table first
    int rowCount=ui->tableWidget->rowCount();
    for(int i=0;i<rowCount;i++)
    {
        ui->tableWidget->removeRow(0);
    }
    ui->tableWidget->setSortingEnabled(false);

    int nOldRowCount=0;
    std::vector<pRequestInfo> requests=(*allCompleteRequests)[RoomID.toStdString()];
    for(pRequestInfo& request:requests)
    {
        ui->tableWidget->insertRow(nOldRowCount);

        QString start_time=QString::fromStdString(request->start_time);
        addItemToRow(nOldRowCount,0,start_time);

        QString end_time=QString::fromStdString(request->end_time);
        addItemToRow(nOldRowCount,1,end_time);

        QString velocity=QString::fromStdString(request->velocity);
        addItemToRow(nOldRowCount,2,velocity);

        QString start_temp=QString::number(request->start_temperature);
        addItemToRow(nOldRowCount,3,start_temp);

        QString end_temp=QString::number(request->end_temperature);
        addItemToRow(nOldRowCount,4,end_temp);

        QString fee=QString::number(request->fee);
        addItemToRow(nOldRowCount,5,fee);

    }

    ui->tableWidget->setSortingEnabled(true);
    ui->tableWidget->sortByColumn(0, Qt::AscendingOrder);


    auto oldItems=ui->tableWidget->findItems(oldID,Qt::MatchExactly);
    if(!oldItems.empty())
    {
        ui->tableWidget->setCurrentItem(oldItems[0]);
    }

}

void ReportWidget::addItemToRow(int nOldRow, int numth, QString item)
{
    QTableWidgetItem *itemWidget= new QTableWidgetItem(item);
    ui->tableWidget->setItem(nOldRow, numth, itemWidget);
    itemWidget->setFlags(Qt::ItemIsEnabled);
}
