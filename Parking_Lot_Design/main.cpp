/*
- A parking lot will be having multiple spaces available for different kind of vehicles.
- Each vehicle will be having a parking ticket
- Parking ticket price should be based on space & time of stay
- Payment is done just before exiting and slot will be freed
- A vehicle cannot park in already parked slots
- Vehicle cannot vacate without payment


Key Requirements:
1. A parking lot with multiple slot types.
2. Supports bikes, cars & Trucks.
3. Dynamic slot allocation based on vehicle size.
4. Payment processing with multiple methods.
5. Issuing Entry ticket and exit validation.

Implementation:
1. Using Strategy Design Pattern for Parking Fare Calculation
    1.1. It allows different parking fee calculations for various vehicles & rates.
    1.2. Supports multiple strategies such as Basic Rates or Premium Rates.
    1.3. It enables flexibilty by letting us switch between these strategies dynamically.

2. Using Factory Design Pattern for Vehicle Types Creation
    2.1. It allows easy type of vehicle creation
    2.2. Ensures consistent object creaion.
    2.3. It Helps manage different vehicle types

3. Using Singleton Design Pattern for Parking Lot Management
    3.1. It ensures only one instance of parking lot exists

4. Using Observer Design Pattern for Exit Notification
    4.1. Used to Notify systems when vehicle exits.
*/

#include "Vehicle_Creation.hpp"
#include "Parking_Lot.hpp"

using namespace std;

int main()
{

    // Creating Parking Spots in a parking Lot;
    vector<ParkingSpot *> parkingSpots;
    parkingSpots.push_back(new CarParkingSpot(1));
    parkingSpots.push_back(new CarParkingSpot(2));
    parkingSpots.push_back(new BikeParkingSpot(3));
    // parkingSpots.push_back(new BikeParkingSpot(4));
    // parkingSpots.push_back(new BikeParkingSpot(5));
    // parkingSpots.push_back(new AutoParkingSpot(6));
    // parkingSpots.push_back(new AutoParkingSpot(7));
    // parkingSpots.push_back(new HeavyParkingSpot(8));
    // parkingSpots.push_back(new HeavyParkingSpot(9));

    // Creating Parking Lot
    ParkingLot *parkingLot = new ParkingLot(parkingSpots);

    // Pricing basedo on clients requirement
    ParkingFeeStrategy *basic = new BaseFareRateStrategy();
    ParkingFeeStrategy *premium = new PremiumFareRateStrategy();

    // Creating Vehicles
    Vehicle *bike = VehicleFactory::createVehicle(VehicleType::BIKE, "tg-92", basic);
    Vehicle *car = VehicleFactory::createVehicle(VehicleType::CAR, "Ap-12", premium);
    Vehicle *auto1 = VehicleFactory::createVehicle(VehicleType::AUTO, "od-32", basic);

    ParkingSpot *bikeSpot = parkingLot->parkVehicle(bike);
    ParkingSpot *carSpot = parkingLot->parkVehicle(car);
    ParkingSpot *auto1Spot = parkingLot->parkVehicle(auto1);

    bikeSpot->vacate();
    return 0;
};