#include "ElevatorController.hpp"
#include <limits>
#include <cmath>

void ElevatorController::registerElevator(std::shared_ptr<Elevator> elevator)
{
    elevators.push_back(elevator);
}

void ElevatorController::handleHallRequest(const HallRequest &request)
{
    auto elevator = selectBestElevator(request);
    elevator->addDestination(request.floor);
}

void ElevatorController::step()
{
    for (auto &elevator : elevators)
    {
        elevator->step();
    }
}

std::shared_ptr<Elevator>
ElevatorController::selectBestElevator(const HallRequest &request)
{
    int minScore = std::numeric_limits<int>::max();
    std::shared_ptr<Elevator> best = nullptr;

    for (auto &e : elevators)
    {
        int score = std::abs(e->getCurrentFloor() - request.floor);
        if (score < minScore)
        {
            minScore = score;
            best = e;
        }
    }
    return best;
}
