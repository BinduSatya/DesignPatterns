#include <bits/stdc++.h>
#include "Parking_Spot.hpp"
#include "Vehicle_Creation.hpp"
#pragma once

using namespace std;

class ParkingLot
{
private:
    vector<ParkingSpot *> parkingspots;
    ~ParkingLot() {};

public:
    ParkingLot(vector<ParkingSpot *> parkingspots)
    {
        this->parkingspots = parkingspots;
    }

    ParkingSpot *findAvailableSpot(string vehicleType)
    {
        for (ParkingSpot *spot : parkingspots)
        {
            if (!spot->isOccupied() && spot->getSpotType() == vehicleType)
            {
                return spot;
            }
        }

        return nullptr;
    }

    ParkingSpot *parkVehicle(Vehicle *vehicle)
    {
        ParkingSpot *spot = findAvailableSpot(vehicle->getVehicleType());
        if (spot != nullptr)
        {
            spot->parkVehicle(vehicle);
            cout << "Vehicle is Parked successfully at spot " << spot->getSpotNumber() << endl;
            return spot;
        }
        cout << "No Parking Spots are available for vehicle " << vehicle->getLicenceNumber() << endl;
        return nullptr;
    }

    void vacateSpot(ParkingSpot *spot, Vehicle *vehicle)
    {
        if (spot && spot->isOccupied() && spot->getVehicle() == vehicle)
        {
            spot->vacate();
            cout << "Spot " << spot->getSpotNumber() << " is have vacated now." << endl;
        }
        else
        {
            cout << "Invalid Operation!" << endl;
        }
    }

    ParkingSpot *getSpotByNumber(int spotNumber)
    {
        for (auto it : parkingspots)
        {
            if (it->getSpotNumber() == spotNumber)
                return it;
        }
        return nullptr;
    }

    vector<ParkingSpot *> getParkingSpots()
    {
        return parkingspots;
    }
};