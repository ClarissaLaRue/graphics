#ifndef HEXAGON_H
#define HEXAGON_H

#include <vector>

using std::vector;
using std::pair;

class Hexagon
{
public:
    Hexagon(int startX, int startY, int size, int X, int Y);

private:
    int size;
    //Координаты шестиугольник
    int CoordinateX;
    int CoordinateY;
    //Координаты центра
    int CenterX;
    int CenterY;
    //Координаты точек, задающих шестиугольник
    vector<pair <int, int>> points;
};


#endif // HEXAGON_H
