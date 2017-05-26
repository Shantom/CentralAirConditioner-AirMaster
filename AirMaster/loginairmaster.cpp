#include "loginairmaster.h"

LoginAirMaster::LoginAirMaster()
{
    loadSecretFile();
}

void LoginAirMaster::showSignInWindow()
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

bool LoginAirMaster::addUser(std::string loginName,std::string pass)
{
    if(login2pass[loginName]!="")
    {
        login2pass[loginName]=pass;
    }
    else
    {

    }
}
