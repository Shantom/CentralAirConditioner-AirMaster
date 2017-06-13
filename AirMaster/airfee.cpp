#include "airfee.h"

AirFee::AirFee():feeUnit(2.5)
{

}

void AirFee::updateFeePower(std::string &roomId, float addFee, float addKWH)
{
    if (allFee[roomId] == nullptr){
        allFee[roomId] = new FeePower(0,0);
    }
    allFee[roomId]->fee+= addFee;
    allFee[roomId]->KWH+= addKWH;
}

float AirFee::getFeeUnit() const
{
    return feeUnit;
}

void AirFee::setFeeUnit(float value)
{
    feeUnit = value;
}
