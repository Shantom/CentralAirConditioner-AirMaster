#ifndef REPORTWIDGET_H
#define REPORTWIDGET_H

#include <QWidget>
#include <QTimer>
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

private:
    Ui::ReportWidget *ui;
    QString RoomID;
    std::map<std::string, std::vector<pRequestInfo>>* allCompleteRequests;
    QTimer timer;
    void addItemToRow(int nOldRow, int numth, QString item);
    int time;

public slots:
    void refreshTable();
};

#endif // REPORTWIDGET_H
