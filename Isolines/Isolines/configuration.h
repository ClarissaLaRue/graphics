#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "function.h"

#include <QColor>
#include <QString>
#include <vector>

using std::vector;

class configuration
{
public:
    configuration();
    configuration(int k, int m, int n, vector<QColor> colors, QColor lineColor);
    void setK(int k);
    void setM(int m);
    void setN(int n);
    void setDomain(int a, int b, int c, int d);
    void setColors(vector<QColor> colors);
    void setLineColor(QColor lineColor);
    void setFunction(Function function);
    int getK();
    int getM();
    int getN();
    int getA();
    int getB();
    int getC();
    int getD();
    float getMin();
    float getMax();
    float calculate(int x, int y);
    vector<QColor> getColors();
    Function getFunction();
    QColor getLineColor();
    void findMaxMin(int a, int b, int c, int d);

private:
    int k;
    int m;
    int n;
    int a = 0;
    int b = 400;
    int c = 0;
    int d = 400;
    float min;
    float max;
    vector<QColor> colors;
    QColor lineColor;
    Function function;
};

#endif // CONFIGURATION_H
