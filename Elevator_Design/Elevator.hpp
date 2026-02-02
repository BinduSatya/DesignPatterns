#pragma once
#include <queue>
#include "ElevatorState.hpp"

class Elevator
{
public:
    Elevator(int id, int maxLoad, int maxSpeed);

    void addDestination(int floor);
    void step();
    void triggerEmergency();

    bool isIdle() const;
    int getCurrentFloor() const;
    int getId() const;

private:
    int id;
    int currentFloor;
    int currentLoad;
    int maxLoad;
    int maxSpeed;

    ElevatorState state;
    std::queue<int> destinations;

    void moveToFloor(int floor);
    void openDoor();
};
