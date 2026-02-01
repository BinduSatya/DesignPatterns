@startuml

interface ParkingFeeStrategy {
+calculateFee(type, hours)
}

class BaseFareRateStrategy
class PremiumFareRateStrategy

ParkingFeeStrategy <|-- BaseFareRateStrategy
ParkingFeeStrategy <|-- PremiumFareRateStrategy

class Vehicle {
-licenceNumber : string
-vehicleType : string
-feeStrategy : ParkingFeeStrategy
+getVehicleType()
+getLicenceNumber()
+calculateFee(hours)
}

class Car
class Bike
class Auto
class Heavy
class Other

Vehicle <|-- Car
Vehicle <|-- Bike
Vehicle <|-- Auto
Vehicle <|-- Heavy
Vehicle <|-- Other

class VehicleFactory {
+createVehicle(type, licence, strategy) : Vehicle
}

VehicleFactory --> Vehicle

abstract class ParkingSpot {
-spotNumber : int
-occupied : bool
-vehicle : Vehicle
-spotType : string
+canParkVehicle(v: Vehicle) : bool
+parkVehicle(v: Vehicle)
+vacate()
}

class CarParkingSpot
class BikeParkingSpot
class AutoParkingSpot
class HeavyParkingSpot
class OtherParkingSpot

ParkingSpot <|-- CarParkingSpot
ParkingSpot <|-- BikeParkingSpot
ParkingSpot <|-- AutoParkingSpot
ParkingSpot <|-- HeavyParkingSpot
ParkingSpot <|-- OtherParkingSpot

class ParkingLot {
-parkingSpots : List<ParkingSpot>
+findAvailableSpot(type) : ParkingSpot
+parkVehicle(v: Vehicle) : ParkingSpot
}

ParkingLot o-- ParkingSpot
ParkingLot --> Vehicle

interface PaymentStrategy {
+processPayment(amount)
}

class CreditCardPayment
class UPIPayment
class EMIPayment

PaymentStrategy <|-- CreditCardPayment
PaymentStrategy <|-- UPIPayment
PaymentStrategy <|-- EMIPayment

class Payment {
-amount : double
-strategy : PaymentStrategy
+processPayment()
}

Payment --> PaymentStrategy
ParkingSpot --> Payment

@enduml
