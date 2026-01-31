/*
Strategy Design Pattern for calculating Parking Fee
*/
#include <bits/stdc++.h>
using namespace std;

class ParkingFeeStrategy
{
public:
    virtual double calculateFee(string vehicleType, int durationInHours) = 0;
};

class BaseFareRateStrategy : public ParkingFeeStrategy
{
    double calculateFee(string vehicleType, int durationInHours) override
    {
        if (vehicleType == "car")
            return durationInHours * 10.00;

        else if (vehicleType == "bike")
            return durationInHours * 5.00;
        else if (vehicleType == "auto")
            return durationInHours * 7.50;
        else if (vehicleType == "heavy")
            return durationInHours * 15.00;
        else
            return durationInHours * 10.00;
    }
};

class PremiumFareRateStrategy : public ParkingFeeStrategy
{
    double calculateFee(string vehicleType, int durationInHours) override
    {
        if (vehicleType == "car")
            return durationInHours * 20.00;

        else if (vehicleType == "bike")
            return durationInHours * 10.00;
        else if (vehicleType == "auto")
            return durationInHours * 15.00;
        else if (vehicleType == "heavy")
            return durationInHours * 30.00;
        else
            return durationInHours * 20.00;
    }
};
