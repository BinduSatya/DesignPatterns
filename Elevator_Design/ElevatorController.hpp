#pragma once
#include <vector>
#include <memory>
#include "Elevator.hpp"
#include "HallRequest.hpp"

class ElevatorController
{
public:
    void registerElevator(std::shared_ptr<Elevator> elevator);
    void handleHallRequest(const HallRequest &request);
    void step();

private:
    std::vector<std::shared_ptr<Elevator>> elevators;

    std::shared_ptr<Elevator> selectBestElevator(const HallRequest &request);
};
