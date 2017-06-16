#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <airconditionmaster.h>
#include<requeuehelper.h>
#include <QTimer>
#include "reportwidget.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initWindow();
private slots:
    void on_pushButton_up_clicked();

    void on_pushButton_down_clicked();

    void on_pushButton_cool_clicked();

    void on_pushButton_heat_clicked();

    void on_pushButton_set_clicked();

    void refreshTable();

    void on_tableWidget_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    void addItemToRow(int nOldRow, int numth, QString item);
    Ui::MainWindow *ui;

    // include Master's info, you can change it at main UI
    AirConditionMaster *airMaster;

    ReQueueHelper* resQueueHelper;

    int upperBound=25;
    int lowerBound=18;

    QTimer timer;

    ReportWidget rw;

    std::map<std::string,std::vector<pRequestInfo>>  blank;


};

#endif // MAINWINDOW_H
