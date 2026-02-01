#include <bits/stdc++.h>
#include "Vehicle_Creation.hpp"
#include "Payment_Strategy.hpp"
#pragma once

using namespace std;

class ParkingSpot
{
private:
    int spotNumber;
    bool occupied;
    Vehicle *vehicle;
    string spotType;

public:
    ParkingSpot(int spotNumber, bool isOccupied, string spotType)
    {
        this->occupied = isOccupied;
        this->spotNumber = spotNumber;
        this->spotType = spotType;
    }
    ~ParkingSpot() {}

    bool isOccupied()
    {
        return occupied;
    }

    virtual bool canParkVehicle(Vehicle *vehicle) = 0;

    void parkVehicle(Vehicle *vehicle)
    {
        if (occupied)
        {
            cout << "Spot is already Occupied" << endl;
            return;
        }

        if (!canParkVehicle(vehicle))
        {
            cout << "Spot is not suitable for " + vehicle->getVehicleType() << endl;
            return;
        }

        this->vehicle = vehicle;
        this->occupied = true;
    }

    void vacate()
    {
        if (!occupied)
        {
            cout << "You cannot vacate already empty spot" << endl;
            return;
        }

        PaymentStrategy *payStrategy = nullptr;
        string type;

        cout << "How do you want to pay:\n 1. Credit card \n 2. UPI \n 3. EMI" << endl;
        cin >> type;

        int retry = 0;
        while (!payStrategy && retry <= 3)
        {
            retry++;
            if (type == "1")
                payStrategy = new CreditCardPayment();
            else if (type == "2")
                payStrategy = new UPIPayment();
            else if (type == "3")
                payStrategy = new EMIPayment();
            else
            {
                cout << "Please select valid selection" << endl;
            }
        }
        payStrategy = new EMIPayment();

        int hours;
        cout << "Enter duration in hours:" << endl;
        cin >> hours;

        double fees = vehicle->calculateFee(hours);

        Payment *pay = new Payment(fees, payStrategy);
        pay->processPayment();

        this->vehicle = nullptr;
        this->occupied = false;
    }

    int getSpotNumber()
    {
        return this->spotNumber;
    }

    Vehicle *getVehicle()
    {
        if (occupied)
            return this->vehicle;
        else
            return nullptr;
    }

    string getSpotType()
    {
        return this->spotType;
    }
};

class CarParkingSpot : public ParkingSpot
{
public:
    CarParkingSpot(int spotNumber) : ParkingSpot(spotNumber, false, "car") {}

    bool canParkVehicle(Vehicle *vehicle) override
    {
        return vehicle->getVehicleType() == "car";
    }
};

class BikeParkingSpot : public ParkingSpot
{
public:
    BikeParkingSpot(int spotNumber) : ParkingSpot(spotNumber, false, "bike") {}

    bool canParkVehicle(Vehicle *vehicle) override
    {
        return vehicle->getVehicleType() == "bike";
    }
};

class AutoParkingSpot : public ParkingSpot
{
public:
    AutoParkingSpot(int spotNumber) : ParkingSpot(spotNumber, false, "auto") {}

    bool canParkVehicle(Vehicle *vehicle) override
    {
        return vehicle->getVehicleType() == "auto";
    }
};

class HeavyParkingSpot : public ParkingSpot
{
public:
    HeavyParkingSpot(int spotNumber) : ParkingSpot(spotNumber, false, "heavy") {}

    bool canParkVehicle(Vehicle *vehicle) override
    {
        return vehicle->getVehicleType() == "heavy";
    }
};

class OtherParkingSpot : public ParkingSpot
{
public:
    OtherParkingSpot(int spotNumber) : ParkingSpot(spotNumber, false, "other") {}

    bool canParkVehicle(Vehicle *vehicle) override
    {
        return vehicle->getVehicleType() == "other";
    }
};