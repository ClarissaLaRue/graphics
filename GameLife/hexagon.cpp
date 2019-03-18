#include <math.h>
#include "hexagon.h"

Hexagon::Hexagon(int startX, int startY, int size, int X, int Y)
{
    this->size = size;
    int halfSize = (int) size / 2;
    int halfSizeSqrt3 = (int) halfSize * sqrt(3);
    int x = startX;
    int y = startY;
    points.push_back(std::make_pair(x,y));
    points.push_back(std::make_pair(x + halfSizeSqrt3, y - halfSize));
    points.push_back(std::make_pair(x + halfSizeSqrt3 + halfSizeSqrt3, y));
    points.push_back(std::make_pair(x + halfSizeSqrt3 + halfSizeSqrt3, y + size));
    points.push_back(std::make_pair(x, y + size));
    points.push_back(std::make_pair(x + halfSizeSqrt3, y + size + halfSize));
    CenterX = x + halfSizeSqrt3;
    CenterY = y + halfSize;
    CoordinateX = X;
    CoordinateY = Y;
}
