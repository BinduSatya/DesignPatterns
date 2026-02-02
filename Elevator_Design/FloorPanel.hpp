#pragma once
#include "ElevatorController.hpp"
#include "Direction.hpp"

class FloorPanel
{
public:
    FloorPanel(int floor, ElevatorController &controller);

    void pressUp();
    void pressDown();

private:
    int floor;
    ElevatorController &controller;
};
