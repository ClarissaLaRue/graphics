#include "map.h"

#include <QPainter>
#include <QColor>
#include <iostream>

Map::Map(QWidget *parent) : QWidget(parent)
{

}

void Map::addConfig(configuration config){
    this->config = config;
    min = config.getMin();
    max = config.getMax();
    findColorRange();
}

void Map::paintEvent(QPaintEvent *){
    draw();
}

void Map::draw(){
    QPainter p(this);
    int startX = 0;
    int startY = 0;
    QPoint start(startX, startY);
    QImage image(size(), QImage::Format_ARGB32);
    unsigned char *bits = image.bits();
    qint32 len = image.bytesPerLine();

    int a = config.getA();
    int b = config.getB();
    int c = config.getC();
    int d = config.getD();

    int x = 0;
    int y = 0;
    int pos = 4 * x + y * len;
    unsigned char *ptr = &bits[pos];

    for (int i = a; i < b; i++){
        for (int j = c; j < d; j++){
              fillPix(ptr, chooseColor(config.calculate(i, j)));
              pos += len;
              ptr = &bits[pos];
        }
        pos -= len*(d-c);
        pos += 4;

        ptr = &bits[pos];
    }
    if (needGrid){
        drawGrid(bits, len);
    }

    p.drawImage(start, image);

    if (needLsolines){
        drawIsolines(p);
    }

    if (needPoint){
        for(int i = 0; i < inPoint.size(); i++){
            p.drawEllipse(inPoint[i].first + startX, inPoint[i].second + startY, 3, 3);
        }
    }
}

void Map::fillPix(unsigned char *ptr, QColor color){
    ptr[0] = color.blue();
    ptr[1] = color.green();
    ptr[2] = color.red();
    ptr[3] = 0xff;
}

//находим границы значений функии для цвет
void Map::findColorRange(){
    float range = abs(max - min) / config.getN();
    vector<QColor> color = config.getColors();
    for (int i = 0; i < config.getN(); i++){
        Colors newColor = Colors();
        newColor.from = min + (i * range);
        newColor.to = newColor.from + range;
        newColor.color = color[i];
        colors.push_back(newColor);
    }
}

//выбираем нужный цвет для значения функции
QColor Map::chooseColor(float f){
    for (int i = 0; i < config.getN(); i++){
        if ((colors[i].from <= f) && (colors[i].to >= f)){
            return colors[i].color;
        }
    }
}

void Map::drawIsolines(QPainter &p){
    int stepX = abs(config.getB() - config.getA()) / config.getK();
    int stepY = abs(config.getD() - config.getC()) / config.getK();
    int x = 0;
    int y = 0;
    int pointCount = 0;
    int pointsInCell = 0;
    float z;
    float f1;
    float f2;
    float f3;
    float f4;
    for (int i = 0; i < config.getK(); i++){
        for(int m = 0; m < config.getM(); m++){
            f1 = config.calculate(x, y);
            f2 = config.calculate(x+stepX, y);
            f3 = config.calculate(x, y+stepY);
            f4 = config.calculate(x+stepX, y+stepY);
            for (int j = 0; j < config.getN(); j++){
                z = colors[j].to;
                //точки входа для верхних граней
                if (!(f1 < z && f2 < z) && !(f1 > z && f2 > z)){
                    inPoint.push_back(std::make_pair(x + stepX * ( z - f1)/(f2 - f1), y));
                    pointCount++;
                    pointsInCell++;
                }

                //точки входа для нижних граней
                if (!(f3 < z && f4 < z) && !(f3 > z && f4 > z)){
                    inPoint.push_back(std::make_pair(x + stepX * ( z - f3)/(f4 - f3), y + stepY));
                    pointCount++;
                    pointsInCell++;
                }

                //точки входа для правых граней
                if (!(f2 < z && f4 < z) && !(f2 > z && f4 > z)){
                    inPoint.push_back(std::make_pair(x + stepX ,y + stepY * (z - f2)/(f4 - f2)));
                    pointCount++;
                    pointsInCell++;
                }

                //точки входа для левых граней
                if (!(f3 < z && f1 < z) && !(f3 > z && f1 > z)){
                    inPoint.push_back(std::make_pair(x , y + stepY  * (z - f1)/(f3 - f1)));
                    pointCount++;
                    pointsInCell++;
                }

                //в клетке больше точек, чем две, даже если по одной линии
//                if (pointsInCell == 2){
//                    p.drawLine(inPoint[pointCount-1].first, inPoint[pointCount-1].second, inPoint[pointCount-2].first, inPoint[pointCount-2].second);
//                }

                std::cout<<i<<" "<< m<< " " <<pointsInCell<<std::endl;

                pointsInCell = 0;
            }
            y += stepY;
        }
        x += stepX;
        y=0;
    }
}

void Map::grid(){
    needGrid = !needGrid;
    repaint();
}

void Map::isolines(){
    needLsolines = !needLsolines;
    repaint();
}

void Map::point(){
    needPoint = !needPoint;
    repaint();
}

void Map::drawGrid(unsigned char *bits, qint32 len){
    int step = abs(config.getB() - config.getA()) / config.getK();
    int x = 0;
    for (int i = 0; i < config.getK() - 1; i++){
        x += step;
        drawVerticalLine(x, 0, x, abs(config.getD() - config.getC()), bits, len);
    }
    step = abs(config.getD() - config.getC()) / config.getK();
    int y = 0;
    for (int i = 0; i < config.getM() - 1; i++){
        y += step;
        drawHorizontalLine(0, y, abs(config.getB() - config.getA()), y,  bits, len);
    }
}


void Map::drawVerticalLine(int x0, int y0, int x1, int y1, unsigned char *bits, qint32 len){
    unsigned char *ptr = &bits[4 * x0 + y0 * len];
    fillPix(ptr, config.getLineColor());
    for( int i=0; i<abs(y0-y1); ++i) {
        fillPix(ptr, config.getLineColor());
        ptr += len;
    }
}

void Map::drawHorizontalLine(int x0, int y0, int x1, int y1, unsigned char *bits, qint32 len){
    unsigned char *ptr = &bits[4 * x0 + y0 * len];
    fillPix(ptr, config.getLineColor());
    for( int i=0; i<abs(x0-x1); ++i) {
        fillPix(ptr, config.getLineColor());
        ptr += 4;
    }
}
