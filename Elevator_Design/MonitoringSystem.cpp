#include "MonitoringSystem.hpp"
#include <iostream>

using namespace std;

void MonitoringSystem::logElevator(const shared_ptr<Elevator> &e)
{
    cout << "Elevator " << e->getId()
         << " at floor " << e->getCurrentFloor() << endl;
}
