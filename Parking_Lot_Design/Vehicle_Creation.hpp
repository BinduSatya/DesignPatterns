/*
Factory Design Pattern for creating Vehicle Types
*/

#pragma once
#include <bits/stdc++.h>
#include "VehicleType.hpp"
#include "Parking_Fee_Strategy.hpp"

using namespace std;

class Vehicle
{
protected:
    string licenceNumber;
    VehicleType vehicleType;
    ParkingFeeStrategy *feeStrategy;

public:
    Vehicle(string lic, VehicleType vehType, ParkingFeeStrategy *feeStra)
    {
        this->licenceNumber = lic;
        this->vehicleType = vehType;
        this->feeStrategy = feeStra;
    }

    virtual ~Vehicle() = default;

    VehicleType getVehicleType() const
    {
        return vehicleType;
    }

    string getLicenceNumber() const
    {
        return licenceNumber;
    }
    ParkingFeeStrategy *getStrategy() const
    {
        return feeStrategy;
    }
};

class Car : public Vehicle
{
public:
    Car(string lic, ParkingFeeStrategy *feeStra) : Vehicle(lic, VehicleType::CAR, feeStra) {};
};

class Bike : public Vehicle
{
public:
    Bike(string lic, ParkingFeeStrategy *feeStra) : Vehicle(lic, VehicleType::BIKE, feeStra) {};
};

class Auto : public Vehicle
{
public:
    Auto(string lic, ParkingFeeStrategy *feeStra) : Vehicle(lic, VehicleType::AUTO, feeStra) {};
};

class Heavy : public Vehicle
{
public:
    Heavy(string lic, ParkingFeeStrategy *feeStra) : Vehicle(lic, VehicleType::HEAVY, feeStra) {};
};

class Other : public Vehicle
{
public:
    Other(string lic, ParkingFeeStrategy *feeStra) : Vehicle(lic, VehicleType::OTHER, feeStra) {};
};

class VehicleFactory
{
public:
    static Vehicle *createVehicle(VehicleType vehicleType, string licenceNumber, ParkingFeeStrategy *parkingFeeType)
    {
        if (vehicleType == VehicleType::CAR)
        {
            return new Car(licenceNumber, parkingFeeType);
        }
        else if (vehicleType == VehicleType::BIKE)
        {
            return new Bike(licenceNumber, parkingFeeType);
        }
        else if (vehicleType == VehicleType::AUTO)
        {
            return new Auto(licenceNumber, parkingFeeType);
        }
        else if (vehicleType == VehicleType::HEAVY)
        {
            return new Heavy(licenceNumber, parkingFeeType);
        }
        else
        {
            return new Other(licenceNumber, parkingFeeType);
        }
    }
};