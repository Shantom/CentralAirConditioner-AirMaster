#include "loginairmaster.h"

LoginAirMaster::LoginAirMaster()
{
    loadSecretFile();
}

void LoginAirMaster::showSignInWindow()
{

}

bool LoginAirMaster::signIn()
{
    //update loginName and password
    //TODO
    if(!judgeSignInValid())
        return false;

    return verifyCurrentUser();
}

bool LoginAirMaster::signUp()
{
    //update loginName and password
    //TODO
    if(!judgeSignUpValid())
        return false;

    return addUser();
}

bool LoginAirMaster::judgeSignUpValid()
{

}

bool LoginAirMaster::judgeSignInValid()
{

}

bool LoginAirMaster::loadSecretFile()
{
    std::fstream readSecret("pas.air");
    if(!readSecret.is_open())
    {
        readSecret.close();
        //QDebug()<<"can't open pas.air for login master. \n";
        return false;
    }
    else
    {
        std::string line;
        int counter=0;
        while(std::getline(readSecret,line))
        {
            std::stringstream ssLine(line);
            std::string loginN,passW;
            ssLine>>loginN>>passW;
            login2pass[loginN]=passW;
            counter++;
        }

        if(counter==0)
        {
            login2pass["admin"]=AirEncrypter::encryptString("admin").toStdString();
            readSecret<<"admin  "+login2pass["admin"]+"\n";
        }
        readSecret.close();

        return true;
    }
}

bool LoginAirMaster::verifyCurrentUser()
{
    std::string passEncrypt=AirEncrypter::encryptString(password).toStdString();
    if(passEncrypt==login2pass[loginName.toStdString()])
        return true;
    else
        return false;
}

bool LoginAirMaster::addUser()
{
    if(login2pass[loginName.toStdString()]!="")
    {
        login2pass[loginName.toStdString()]=password.toStdString();
    }
    else
    {

    }
}
