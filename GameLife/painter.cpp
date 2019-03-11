#include "painter.h"
#include "math.h"
#include <iostream>
#include <QImage>
#include <QPainter>
#include <QSize>
#include <QMouseEvent>

Painter::Painter(QWidget *parent) {

}


Painter::Painter(QWidget *parent, int x, int y) : QWidget(parent){

}


void Painter::paintEvent(QPaintEvent *){
    QPainter p(this);
    draw(p);
}

void mouseMoveEvent(QMouseEvent *e){
    int x = e->x();
    int y = e->y();
}

void mousePressEvent(QMouseEvent *e){

}

void wheelEvent(QWheelEvent *e){

}

void Painter::draw(QPainter &p){
    QImage image(size(), QImage::Format_ARGB32);
    unsigned char *bits = image.bits();
    qint32 len = image.bytesPerLine();
    int cellSize = 20;
    int halfSize = (int) cellSize / 2;
    int halfSizeSqrt3 = (int) halfSize * sqrt(3);
    //int M = 15;
    int N = 9;
    drawField(cellSize, halfSize, halfSizeSqrt3, bits, len, M, N);
    QPoint start(0, 0);
    p.drawImage(start, image);

}

void Painter::fillPixforLine(int x, int y, unsigned char *bits, qint32 len){
    //QColor c;  c.red();
    bits[4 * x + y * len] = 0;//qRed(0xff000000);
    bits[4 * x + y * len + 1] = 0;//qGreen(0xff000000);
    bits[4 * x + y * len + 2] = 0;//qBlue(0xff000000);
    bits[4 * x + y * len + 3] = 0xff;//qAlpha(0xff000000);
}

//рисуем восходящую линию
void Painter::drawAscendingLine(int x0, int y0, int x1, int y1, unsigned char *bits, qint32 len){
    unsigned char *ptr = &bits[4 * x0 + y0 * len];
    *ptr = 0;
    ptr[1] = 0;
    ptr[2] = 0;
    ptr[3] = 0xff;
    int dx = abs(x0-x1);
    int dy = abs(y0-y1);
    int err = -dx;
    for( int i=0; i<dx; ++i) {
        ptr += 4;
        err += 2*dy;
        if (err > 0) {
            err -= 2*dx;
            ptr -= len;
        }
        *ptr = 0;
        ptr[1] = 0;
        ptr[2] = 0;
        ptr[3] = 0xff;
    }
}

//рисует убывающую линию
void Painter::drawDescendingLine(int x0, int y0, int x1, int y1, unsigned char *bits, qint32 len){
    unsigned char *ptr = &bits[4 * x0 + y0 * len];
    *ptr = 0;
    ptr[1] = 0;
    ptr[2] = 0;
    ptr[3] = 0xff;
    int dx = abs(x0-x1);
    int dy = abs(y0-y1);
    int err = -dx;
    for( int i=0; i<dx; ++i) {
        ptr += 4;
        err += 2*dy;
        if (err > 0) {
            err -= 2*dx;
            ptr += len;
        }
        *ptr = 0;
        ptr[1] = 0;
        ptr[2] = 0;
        ptr[3] = 0xff;
    }
}

//рисуем вертикальную линию
void Painter::drawVerticalLine(int x0, int y0, int x1, int y1, unsigned char *bits, qint32 len){
    unsigned char *ptr = &bits[4 * x0 + y0 * len];
    *ptr = 0;
    ptr[1] = 0;
    ptr[2] = 0;
    ptr[3] = 0xff;
    for( int i=0; i<abs(y0-y1); ++i) {
        ptr += len;
        *ptr = 0;
        ptr[1] = 0;
        ptr[2] = 0;
        ptr[3] = 0xff;
    }
}

//рисуем 6 угольни
void Painter::drawHexagon(int x, int y, int cellSize, int halfSize, int halfSizeSqrt3, unsigned char *bits, qint32 len){
    drawAscendingLine(x, y, x + halfSizeSqrt3, y - halfSize, bits, len);
    drawDescendingLine(x + halfSizeSqrt3, y - halfSize, x + halfSizeSqrt3 + halfSizeSqrt3, y, bits, len);
    drawVerticalLine(x + halfSizeSqrt3 + halfSizeSqrt3, y, x + halfSizeSqrt3 + halfSizeSqrt3, y + cellSize, bits, len);
    drawVerticalLine(x, y, x, y + cellSize, bits, len);
    drawDescendingLine(x, y + cellSize, x + halfSizeSqrt3, y + cellSize + halfSize, bits, len);
    drawAscendingLine(x + halfSizeSqrt3, y + cellSize + halfSize, x + halfSizeSqrt3 + halfSizeSqrt3, y + cellSize, bits, len);
}

void Painter::drawHexagonLine(int x, int y, int cellSize, int halfSize, int halfSizeSqrt3, unsigned char *bits, qint32 len, int M){
    for(int i = 0; i < M; i++){
        drawHexagon(x, y, cellSize, halfSize, halfSizeSqrt3, bits, len);
        x += 2 * halfSizeSqrt3;
    }
}

void Painter::drawField(int cellSize, int halfSize, int halfSizeSqrt3, unsigned char *bits, qint32 len, int M, int N){
    int x = 0;
    int y = halfSize;
    bool even = false;
    for (int i = 0; i < N; i++){
        if (even){
            drawHexagonLine(x + halfSizeSqrt3, y, cellSize, halfSize, halfSizeSqrt3, bits, len, M - 1);
        }else {
            drawHexagonLine(x, y, cellSize, halfSize, halfSizeSqrt3, bits, len, M);
        }
        y += cellSize + halfSize;
        even = !even;
    }
}

void Painter::span(unsigned char *bits, qint32 len){


}

Painter::~Painter(){}
