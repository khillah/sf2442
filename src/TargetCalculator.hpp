#pragma once

#include "Coordinates.hpp"
#include <cmath>

struct TargetCalculator
{
    Coordinates calculate(const Coordinates& ship,
                          const Coordinates& prev,
                          const Coordinates& target,
                          const Coordinates& next)
    {
        Solution first(ship, target);
        Solution second(target, next);

        double x = (first.target.x + second.target.x) / 2.0;
        double y = (first.target.y + second.target.y) / 2.0;

        return Coordinates(static_cast<int>(x), static_cast<int>(y));


//        return bezierCurve(0.3, ship, target, next);

//        return next;
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

    struct Solution
    {
        constexpr static double rr = 600 * 600;

        Solution(const Coordinates& prev,
                 const Coordinates& next)
        {
            LinearFunction line(prev, next);

            double a = (1 + line.a * line.a);
            double b = (2 * line.a * line.b - 2 * next.x - 2 * line.a * next.y);
            double c = (0
                        + next.x * next.x
                        + next.y * next.y
                        + line.b * line.b
                        - rr
                        - 2 * line.b * next.y
                        );
            // d needs to be >= 0
            double d = std::sqrt(b * b - 4 * a * c);

            double x1 = (-b - d) / (2 * a);
            double y1 = line.a * x1 + line.b;
            target = Coordinates(static_cast<int>(x1), static_cast<int>(y1));
            if(target.distance(next) > prev.distance(next))
            {
                double x2 = (-b + d) / (2 * a);
                double y2 = line.a * x2 + line.b;

                target = Coordinates(static_cast<int>(x2), static_cast<int>(y2));
            }
        }

        Coordinates target;
    };

};
