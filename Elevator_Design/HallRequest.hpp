#pragma once
#include "Direction.hpp"

struct HallRequest
{
    int floor;
    Direction direction;

    HallRequest(int f, Direction d) : floor(f), direction(d) {}
};
