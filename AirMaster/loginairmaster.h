#ifndef LOGINAIRMASTER_H
#define LOGINAIRMASTER_H

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <QString>
#include <QDebug>
#include <airencrypter.h>

class LoginAirMaster
{
public:
    LoginAirMaster();
    void changePassword();
    void showSignInWindow();
    void showSignUpWindow();

private:
    // 加载密码文件
    bool loadSecretFile();
    bool verifyCurrentUser();
    bool addUser(std::string loginName,std::string pass);
    QString loginName;
    QString password;
    std::map<std::string,std::string> login2pass;  // loginName to password (encrypted)
};

#endif // LOGINAIRMASTER_H
