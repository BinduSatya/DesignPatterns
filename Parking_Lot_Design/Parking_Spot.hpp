#pragma once

#include <bits/stdc++.h>
#include "Vehicle_Creation.hpp"
#include "Payment_Strategy.hpp"
#include "VehicleType.hpp"

using namespace std;

class ParkingSpot
{
private:
    int spotNumber;
    bool occupied;
    Vehicle *vehicle;
    VehicleType capacity;
    ParkingFeeStrategy *strategy;

public:
    ParkingSpot(int spotNumber, bool isOccupied, VehicleType capacity)
    {
        this->occupied = isOccupied;
        this->spotNumber = spotNumber;
        this->capacity = capacity;
    }
    ~ParkingSpot() {}

    bool isOccupied()
    {
        return occupied;
    }

    bool canParkVehicle(Vehicle *vehicle)
    {
        return static_cast<int>(vehicle->getVehicleType()) <= static_cast<int>(getSpotType());
    };

    void parkVehicle(Vehicle *vehicle)
    {
        if (occupied)
        {
            cout << "Spot is already Occupied" << endl;
            return;
        }

        if (!canParkVehicle(vehicle))
        {
            cout << "Spot is not suitable for " + static_cast<int>(vehicle->getVehicleType()) << endl;
            return;
        }
        strategy = vehicle->getStrategy();
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

        int retry = 0;
        while (!payStrategy && retry <= 3)
        {
            cout << "How do you want to pay:\n 1. Credit card \n 2. UPI \n 3. EMI" << endl;
            cin >> type;
            cout << endl;
            retry++;
            if (type == "1")
            {
                payStrategy = new CreditCardPayment();
                break;
            }
            else if (type == "2")
            {
                payStrategy = new UPIPayment();
                break;
            }
            else if (type == "3")
            {
                payStrategy = new EMIPayment();
                break;
            }
            else
            {
                cout << "Please select valid selection" << endl;
            }
        }
        if (!payStrategy)
            payStrategy = new EMIPayment();

        int hours;
        cout << "Enter duration in hours:" << endl;
        cin >> hours;
        cout << endl;

        double fees = strategy->calculateFee(capacity, hours);
        cout << "Your fee : " << fees << endl;
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
        {
            cout << "No vehicle is parked here";
            return nullptr;
        }
    }

    VehicleType getSpotType()
    {
        return capacity;
    }
};

class CarParkingSpot : public ParkingSpot
{
public:
    CarParkingSpot(int spotNumber) : ParkingSpot(spotNumber, false, VehicleType::CAR) {}
};

class BikeParkingSpot : public ParkingSpot
{
public:
    BikeParkingSpot(int spotNumber) : ParkingSpot(spotNumber, false, VehicleType::BIKE) {}
};

class AutoParkingSpot : public ParkingSpot
{
public:
    AutoParkingSpot(int spotNumber) : ParkingSpot(spotNumber, false, VehicleType::AUTO) {}
};

class HeavyParkingSpot : public ParkingSpot
{
public:
    HeavyParkingSpot(int spotNumber) : ParkingSpot(spotNumber, false, VehicleType::HEAVY) {}
};

class OtherParkingSpot : public ParkingSpot
{
public:
    OtherParkingSpot(int spotNumber) : ParkingSpot(spotNumber, false, VehicleType::OTHER) {}
};