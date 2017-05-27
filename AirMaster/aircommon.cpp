#include<aircommon.h>


void lowerStr(std::string& str)
{
    for(auto& i:str)
    {
        i=std::tolower(i);
    }
}
