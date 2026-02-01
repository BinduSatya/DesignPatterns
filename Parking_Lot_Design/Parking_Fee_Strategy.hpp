/*
Strategy Design Pattern for calculating Parking Fee
*/
#pragma once
#include <bits/stdc++.h>
#include "VehicleType.hpp"
using namespace std;

class ParkingFeeStrategy
{
public:
    virtual double calculateFee(VehicleType spotType, int durationInHours) = 0;
    ~ParkingFeeStrategy() {};
};

class BaseFareRateStrategy : public ParkingFeeStrategy
{
public:
    double calculateFee(VehicleType spotType, int durationInHours) override
    {
        switch (spotType)
        {
        case VehicleType::CAR:
            return durationInHours * 10.0;

        case VehicleType::BIKE:
            return durationInHours * 5.0;

        case VehicleType::AUTO:
            return durationInHours * 7.5;

        case VehicleType::HEAVY:
            return durationInHours * 15.0;

        case VehicleType::OTHER:
            return durationInHours * 10.0;

        default:
            return durationInHours * 10.0;
        }
    }
};

class PremiumFareRateStrategy : public ParkingFeeStrategy
{
public:
    double calculateFee(VehicleType spotType, int durationInHours) override
    {
        switch (spotType)
        {
        case VehicleType::CAR:
            return durationInHours * 20.00;

        case VehicleType::BIKE:
            return durationInHours * 10.00;

        case VehicleType::AUTO:
            return durationInHours * 15.00;

        case VehicleType::HEAVY:
            return durationInHours * 30.00;

        case VehicleType::OTHER:
            return durationInHours * 20.00;

        default:
            return durationInHours * 10.0;
        }
    }
};
