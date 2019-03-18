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
    points.push_back(std::make_pair(x + halfSizeSqrt3, y + size + halfSize));
    points.push_back(std::make_pair(x, y + size)); // тут был другой порядок ?
    CenterX = x + halfSizeSqrt3;
    CenterY = y + halfSize;
    CoordinateX = X;
    CoordinateY = Y;
    needColor = false;
    colored = false;
}

int Hexagon::getSize(){
    return size;
}

int Hexagon::getCoordinateX(){
    return CoordinateX;
}

int Hexagon::getCoordinateY(){
    return CoordinateY;
}

int Hexagon::getCenterX(){
    return CenterX;
}

int Hexagon::getCenterY(){
    return CenterY;
}

void Hexagon::setNeedColor(bool color){
    needColor = color;
}
bool Hexagon::isNeedColor(){
    return needColor;
}

void Hexagon::setColored(bool color){
    colored = color;
}
bool Hexagon::isColored(){
    return colored;
}

pair <int, int> Hexagon::getPoint(int index){
    return points[index];
}
