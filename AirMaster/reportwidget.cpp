#include "reportwidget.h"
#include "ui_reportwidget.h"

ReportWidget::ReportWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReportWidget)
{
    ui->setupUi(this);
    ui->radioButton_month->toggle();
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

void ReportWidget::setRoom(QString RoomID, int time, std::map<std::string, std::vector<pRequestInfo> > *allCompleteRequests)
{
    this->RoomID=RoomID;
    ui->label_roomid->setText(RoomID);
    this->allCompleteRequests=allCompleteRequests;
    this->time=time;
    ui->label_times->setText(QString::number(time));
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

    std::vector<std::string> invalidRooms=filterRequests(requests);

    for(pRequestInfo& request:requests)
    {
        int isInValid=std::count(invalidRooms.begin(),invalidRooms.end(),request->start_time);
        if(isInValid!=0)
            continue;

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

std::vector<std::string> ReportWidget::filterRequests(std::vector<pRequestInfo> &requests)
{
    std::vector<std::string> invalidReports;

    if(reportType==ALL)
        return invalidReports;

    for(pRequestInfo& request:requests)
    {
        QDate thisDate=QDateTime::fromString(QString::fromStdString(request->start_time),
                                             "yyyy-MM-dd--hh-mm-ss").date();
//        qDebug()<<thisDate.toString();
        switch (reportType) {
        case MONTH:
            if(thisDate.month()!=date.month())
            {
                invalidReports.push_back(request->start_time);
            }
            break;
        case WEEK:
            if(thisDate.weekNumber()!=date.weekNumber())
            {
                invalidReports.push_back(request->start_time);
            }
            break;
        case DAY:
            if(thisDate.day()!=date.day())
            {
                invalidReports.push_back(request->start_time);
            }
            break;

        default:
            break;
        }
    }
    return invalidReports;
}

void ReportWidget::on_radioButton_month_toggled(bool checked)
{
    if(checked)
        reportType=MONTH;
}

void ReportWidget::on_radioButton_week_toggled(bool checked)
{
    if(checked)
        reportType=WEEK;
}

void ReportWidget::on_radioButton_day_toggled(bool checked)
{
    if(checked)
        reportType=DAY;
}

void ReportWidget::on_dateEdit_editingFinished()
{
    date=ui->dateEdit->dateTime().date();
}

void ReportWidget::on_radioButton_all_toggled(bool checked)
{
    if(checked)
        reportType=ALL;

}
