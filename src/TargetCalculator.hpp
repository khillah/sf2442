#pragma once

#include "Coordinates.hpp"
#include <cmath>
#include <stdexcept>

struct LinearFunction
{
    LinearFunction(const Coordinates& p0, const Coordinates& p1)
    {
        a = (p0.y - p1.y) / (p0.x - p1.x);
        b = p0.y - a * p0.x;
    }
    double a;
    double b;
};

struct TrinomialExpression
{
    TrinomialExpression(double a, double b, double c)
    {
        double delta = b * b - 4 * a * c;
        if(delta < 0)
        {
            throw std::runtime_error("TrinomialExpression: delta < 0");
        }

        double d = std::sqrt(delta);

        double x1 = (-b - d) / (2 * a);
        double y1 = (a * x1 * x1) + (b * x1) + c;
        s1 = Coordinates(static_cast<int>(x1), static_cast<int>(y1));

        double x2 = (-b + d) / (2 * a);
        double y2 = (a * x2 * x2) + (b * x2) + c;
        s2 = Coordinates(static_cast<int>(x2), static_cast<int>(y2));
    }

    Coordinates s1;
    Coordinates s2;
};

struct Vector
{
    Vector(const Coordinates& begin, const Coordinates& end) :
        x(end.x - begin.x),
        y(end.y - begin.y)
    {}

    Vector& normalize()
    {
        double len = std::sqrt(x * x + y * y);
        x /= len;
        y /= len;
        return *this;
    }

    Coordinates translateGivenPointTimes(const Coordinates& point, int times)
    {
        return
        {
            static_cast<int>(point.x + times * x),
            static_cast<int>(point.y + times * y)
        };
    }

    double x;
    double y;
};

struct LineCircleNearestIntersection
{
    LineCircleNearestIntersection(const Coordinates& prev,
                                  const Coordinates& next)
    {
        Vector v(next, prev);
        v.normalize();
        target = v.translateGivenPointTimes(next, 600);
    }

    Coordinates target;
};

struct TargetCalculator
{
    Coordinates calculate(const Coordinates& ship,
                          const Coordinates& target,
                          const Coordinates& next)
    {
        LineCircleNearestIntersection first(ship, target);
        LineCircleNearestIntersection second(next, target);

        double x = (first.target.x + second.target.x) / 2.0;
        double y = (first.target.y + second.target.y) / 2.0;

        return Coordinates(static_cast<int>(x), static_cast<int>(y));
    }

private:
    Coordinates bezierCurve(double t,
                            const Coordinates& p0,
                            const Coordinates& p1,
                            const Coordinates& p2)
    {
//        int x = static_cast<int>((1 - t) * (1 - t) * p0.x + 2 * (1 - t) * t * p1.x + t * t * p2.x);
//        int y = static_cast<int>((1 - t) * (1 - t) * p0.y + 2 * (1 - t) * t * p1.y + t * t * p2.y);
        int x = static_cast<int>((p1.x - (1 - t) * (1 - t) * p0.x - t * t * p2.x) / (2 * (1 - t) * t));
        int y = static_cast<int>((p1.y - (1 - t) * (1 - t) * p0.y - t * t * p2.y) / (2 * (1 - t) * t));
        return Coordinates(x, y);
    }
};
