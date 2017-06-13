#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    reject();
    delete ui;
}

void LoginDialog::on_pushButton_login_clicked()
{
    bool result=true;
    //todo
    if(result)
        accept();
    else
    {
        QMessageBox::warning(this,"Error","Wrong administrator infomation.");
    }
}
