#include "mainwindow.h"
#include <QApplication>
#include <airdatabase.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AirDatabase data;
    data.connectDatabase("127.0.0.1",6379);
    //MainWindow w;
    //w.show();

    return a.exec();
}
