/*
Factory Design Pattern for creating Vehicle Types
*/

#include <bits/stdc++.h>
#include <Parking_Fee_Strategy.hpp>

using namespace std;

class Vehicle
{
protected:
    string licenceNumber;
    string vehicleType;
    ParkingFeeStrategy *feeStrategy;

public:
    Vehicle(string lic, string vehType, ParkingFeeStrategy *feeStra)
    {
        this->licenceNumber = lic;
        this->vehicleType = vehType;
        this->feeStrategy = feeStra;
    }

    string getVehicleType()
    {
        return vehicleType;
    }

    string getLicenceNumber()
    {
        return licenceNumber;
    }

    double calculateFee(int duration)
    {
        return feeStrategy->calculateFee(vehicleType, duration);
    }
};

class Car : public Vehicle
{
public:
    Car(string lic, string vehType, ParkingFeeStrategy *feeStra) : Vehicle(lic, "car", feeStra) {};
};

class Bike : public Vehicle
{
public:
    Bike(string lic, string vehType, ParkingFeeStrategy *feeStra) : Vehicle(lic, "bike", feeStra) {};
};

class Auto : public Vehicle
{
public:
    Auto(string lic, string vehType, ParkingFeeStrategy *feeStra) : Vehicle(lic, "auto", feeStra) {};
};

class Heavy : public Vehicle
{
public:
    Heavy(string lic, string vehType, ParkingFeeStrategy *feeStra) : Vehicle(lic, "heavy", feeStra) {};
};

class Other : public Vehicle
{
public:
    Other(string lic, string vehType, ParkingFeeStrategy *feeStra) : Vehicle(lic, "other", feeStra) {};
};

class VehicleFactory
{
public:
    Vehicle *createVehicle(string vehicleType, string licenceNumber, ParkingFeeStrategy *parkingFeeType)
    {
        if (vehicleType == "car")
        {
            return new Car(licenceNumber, vehicleType, parkingFeeType);
        }
        else if (vehicleType == "bike")
        {
            return new Bike(licenceNumber, vehicleType, parkingFeeType);
        }
        else if (vehicleType == "auto")
        {
            return new Auto(licenceNumber, vehicleType, parkingFeeType);
        }
        else if (vehicleType == "heavy")
        {
            return new Heavy(licenceNumber, vehicleType, parkingFeeType);
        }
        else
        {
            return new Other(licenceNumber, vehicleType, parkingFeeType);
        }
    }
};