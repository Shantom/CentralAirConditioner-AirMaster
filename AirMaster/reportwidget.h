#ifndef REPORTWIDGET_H
#define REPORTWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QDate>
#include <QDebug>
#include <algorithm>
#include "aircommon.h"
#include "string"
namespace Ui {
class ReportWidget;
}

class ReportWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReportWidget(QWidget *parent = 0);
    void setRoom(QString RoomID,int time,std::map<std::string, std::vector<pRequestInfo>> *allCompleteRequests);
    ~ReportWidget();
    enum type{
        MONTH,WEEK,DAY,ALL
    };

private:
    Ui::ReportWidget *ui;
    QString RoomID;
    std::map<std::string, std::vector<pRequestInfo>>* allCompleteRequests;
    QTimer timer;
    void addItemToRow(int nOldRow, int numth, QString item);
    std::vector<std::string> filterRequests(std::vector<pRequestInfo> &requests);
    int time;
    type reportType;
    QDate date;

public slots:
    void refreshTable();
private slots:
    void on_radioButton_month_toggled(bool checked);
    void on_radioButton_week_toggled(bool checked);
    void on_radioButton_day_toggled(bool checked);
    void on_dateEdit_editingFinished();
    void on_radioButton_all_toggled(bool checked);
};

#endif // REPORTWIDGET_H
