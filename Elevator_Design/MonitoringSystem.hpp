#pragma once
#include <memory>
#include "Elevator.hpp"

using namespace std;

class MonitoringSystem
{
public:
    void logElevator(const shared_ptr<Elevator> &elevator);
};
