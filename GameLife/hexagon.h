#ifndef HEXAGON_H
#define HEXAGON_H

#include <vector>

using std::vector;
using std::pair;

class Hexagon
{
public:
    Hexagon(int startX, int startY, int size, int X, int Y);
    int getSize();
    int getCoordinateX();
    int getCoordinateY();
    int getCenterX();
    int getCenterY();
    void setNeedColor(bool);
    bool isNeedColor();
    void setColored(bool);
    bool isColored();
    pair <int, int> getPoint(int index);


protected:
    int size;
    //Координаты шестиугольник
    int CoordinateX;
    int CoordinateY;
    //Координаты центра
    int CenterX;
    int CenterY;
    //Координаты точек, задающих шестиугольник
    vector<pair <int, int>> points;
    bool needColor;
    bool colored;
};


#endif // HEXAGON_H
