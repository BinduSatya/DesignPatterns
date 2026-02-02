#include "FloorPanel.hpp"
#include "HallRequest.hpp"

FloorPanel::FloorPanel(int floor, ElevatorController &controller)
    : floor(floor), controller(controller) {}

void FloorPanel::pressUp()
{
    controller.handleHallRequest(HallRequest(floor, Direction::UP));
}

void FloorPanel::pressDown()
{
    controller.handleHallRequest(HallRequest(floor, Direction::DOWN));
}
