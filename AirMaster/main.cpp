#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>
#include <airdatabase.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //AirDatabase data;
    //data.connectDatabase("127.0.0.1",6379);
    LoginDialog ld;
    MainWindow* w;
    if(ld.exec()==QDialog::Accepted)
    {
        w=new MainWindow();
        w->show();
    }
    return a.exec();
}
