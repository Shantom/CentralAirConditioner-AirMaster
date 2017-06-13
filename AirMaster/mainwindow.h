#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <airconditionmaster.h>
#include<requeuehelper.h>
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

private:
    Ui::MainWindow *ui;

    // include Master's info, you can change it at main UI
    AirConditionMaster *airMaster;

    ReQueueHelper* resQueueHelper;

    int upperBound=23;
    int lowerBound=14;

};

#endif // MAINWINDOW_H
