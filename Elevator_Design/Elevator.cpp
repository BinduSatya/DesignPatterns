#include "Elevator.hpp"
#include <cmath>

Elevator::Elevator(int id, int maxLoad, int maxSpeed)
    : id(id),
      currentFloor(0),
      currentLoad(0),
      maxLoad(maxLoad),
      maxSpeed(maxSpeed),
      state(ElevatorState::IDLE) {}

void Elevator::addDestination(int floor)
{
    if (state == ElevatorState::EMERGENCY)
        return;
    destinations.push(floor);
}

void Elevator::step()
{
    if (state == ElevatorState::EMERGENCY)
        return;
    if (!isIdle())
        return;
    if (destinations.empty())
        return;

    int nextFloor = destinations.front();
    destinations.pop();

    moveToFloor(nextFloor);
    openDoor();
}

void Elevator::moveToFloor(int floor)
{
    if (floor == currentFloor)
        return;

    state = (floor > currentFloor)
                ? ElevatorState::MOVING_UP
                : ElevatorState::MOVING_DOWN;

    currentFloor = floor;
    state = ElevatorState::IDLE;
}

void Elevator::openDoor()
{
    if (state != ElevatorState::IDLE)
        return;

    state = ElevatorState::DOOR_OPEN;
    state = ElevatorState::IDLE;
}

void Elevator::triggerEmergency()
{
    state = ElevatorState::EMERGENCY;
    while (!destinations.empty())
        destinations.pop();
}

bool Elevator::isIdle() const
{
    return state == ElevatorState::IDLE;
}

int Elevator::getCurrentFloor() const { return currentFloor; }
int Elevator::getId() const { return id; }
