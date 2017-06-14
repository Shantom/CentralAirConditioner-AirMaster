#ifndef AIRFEE_H
#define AIRFEE_H

#include <string>
#include <map>

typedef struct FeePower{
    float fee;
    float KWH;
    FeePower(float _fee,float _kwh):fee(_fee),KWH(_kwh){};
}FeePower,*pFeePower;

class AirFee
{
public:
    AirFee();
    void updateFeePower(std::string& roomId, float addFee, float addKWH);
    pFeePower getRoomFee(std::string roomId);
    float getFeeUnit() const;

    void setFeeUnit(float value);

private:
    // key is roomId, value is its fee and kwh.
    std::map<std::string, pFeePower> allFee;
    float feeUnit;
};

#endif // AIRFEE_H
