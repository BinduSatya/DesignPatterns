#include <memory>
#include "ElevatorController.hpp"
#include "FloorPanel.hpp"
#include "Elevator.hpp"
#include <bits/stdc++.h>

int main()
{
    std::cout << "Hello there" << std::endl;
    ElevatorController controller;
    std::cout << "Hello there" << std::endl;
    for (int i = 0; i < 5; i++)
    {
        controller.registerElevator(
            std::make_shared<Elevator>(i, 1000, 10));
    }

    FloorPanel floor2(2, controller);
    FloorPanel floor7(7, controller);
    FloorPanel floor10(10, controller);

    floor2.pressUp();
    floor7.pressDown();
    floor10.pressUp();

    while (true)
    {
        controller.step();
    }

    return 0;
}
