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

    void loginAdmin();
    void initWindow();
private:
    Ui::MainWindow *ui;
    AirConditionMaster *airMaster;
    ReQueueHelper* resQueueHelper;


};

#endif // MAINWINDOW_H
