#pragma once

struct Coordinates
{
    Coordinates()
    {}

    Coordinates(const Coordinates& a, const Coordinates& b) :
        x(b.x - a. x),
        y(b.y - a.y)
    {}

    int x;
    int y;
};
