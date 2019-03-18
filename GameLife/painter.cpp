#include "painter.h"
#include "math.h"
#include <iostream>
#include <QImage>
#include <QPainter>
#include <QSize>
#include <QMouseEvent>
#include <stack>
#include "ui_optionsdialog.h"
#include "optionsdialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


using std::stack;
using std::pair;

Painter::Painter(QWidget *parent) : QWidget(parent){
    halfSize = (int) cellSize / 2;
    halfSizeSqrt3 = (int) halfSize * sqrt(3);
}

void Painter::setM(int M){
    this->M = M;
    makeField();
    repaint();
}

void Painter::setN(int N){
    this->N = N;
    makeField();
    repaint();
}
void Painter::setSize(int size){
    this->cellSize = size;
    halfSize = (int) cellSize / 2;
    halfSizeSqrt3 = (int) halfSize * sqrt(3);
    makeField();
    repaint();
}

void Painter::paintEvent(QPaintEvent *){
    QPainter p(this);
    draw(p);
}

//void mouseMoveEvent(QMouseEvent *e){
//    int x = e->x();
//    int y = e->y();
//}

void Painter::mousePressEvent(QMouseEvent *e){

}

//void wheelEvent(QWheelEvent *e){

//}

void Painter::fillPixel(unsigned char *ptr, int color){
    if (color == BLACK){
        ptr[0] = 0;
        ptr[1] = 0;
        ptr[2] = 0;
        ptr[3] = 0xff;
    }
    if (color == BLUE){
        ptr[0] = 0xff;
        ptr[1] = 0;
        ptr[2] = 0;
        ptr[3] = 0xff;
    }
}

void Painter::draw(QPainter &p){
    QImage image(size(), QImage::Format_ARGB32);
    unsigned char *bits = image.bits();
    qint32 len = image.bytesPerLine();
    drawField(bits, len);
    span(halfSizeSqrt3, cellSize,bits, len, WHITE, BLUE);
    QPoint start(0, 0);
    p.drawImage(start, image);
}

//рисуем восходящую линию
void Painter::drawAscendingLine(int x0, int y0, int x1, int y1, unsigned char *bits, qint32 len){
    unsigned char *ptr = &bits[4 * x0 + y0 * len];
    fillPixel(ptr, BLACK);
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
        fillPixel(ptr, BLACK);
    }
}

//рисует убывающую линию
void Painter::drawDescendingLine(int x0, int y0, int x1, int y1, unsigned char *bits, qint32 len){
    unsigned char *ptr = &bits[4 * x0 + y0 * len];
    fillPixel(ptr, BLACK);
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
        fillPixel(ptr, BLACK);
    }
}

//рисуем вертикальную линию
void Painter::drawVerticalLine(int x0, int y0, int x1, int y1, unsigned char *bits, qint32 len){
    unsigned char *ptr = &bits[4 * x0 + y0 * len];
    fillPixel(ptr, BLACK);
    for( int i=0; i<abs(y0-y1); ++i) {
        fillPixel(ptr, BLACK);
        ptr += len;
    }
}

//рисуем 6 угольни
void Painter::drawHexagon(int x, int y, unsigned char *bits, qint32 len){
    drawAscendingLine(x, y, x + halfSizeSqrt3, y - halfSize, bits, len);
    drawDescendingLine(x + halfSizeSqrt3, y - halfSize, x + halfSizeSqrt3 + halfSizeSqrt3, y, bits, len);
    drawVerticalLine(x + halfSizeSqrt3 + halfSizeSqrt3, y, x + halfSizeSqrt3 + halfSizeSqrt3, y + cellSize, bits, len);
    drawVerticalLine(x, y, x, y + cellSize, bits, len);
    drawDescendingLine(x, y + cellSize, x + halfSizeSqrt3, y + cellSize + halfSize, bits, len);
    drawAscendingLine(x + halfSizeSqrt3, y + cellSize + halfSize, x + halfSizeSqrt3 + halfSizeSqrt3, y + cellSize, bits, len);
}

void Painter::drawHexagonLine(int x, int y, unsigned char *bits, qint32 len, int K){
    for(int i = 0; i < K; i++){
        drawHexagon(x, y, bits, len);
        x += 2 * halfSizeSqrt3;
    }
}

//Рисуем поле
void Painter::drawField(unsigned char *bits, qint32 len){
    int x = 0;
    int y = halfSize;
    bool even = false;
    for (int i = 0; i < N; i++){
        if (even){
            drawHexagonLine(x + halfSizeSqrt3, y, bits, len, M - 1);
        }else {
            drawHexagonLine(x, y, bits, len, M);
        }
        y += cellSize + halfSize;
        even = !even;
    }
}

void Painter::span(int x, int y, unsigned char *bits, qint32 len, int oldColor, int newColor){
    stack<Span> spans;
    unsigned char *ptr = &bits[4 * x + y * len];
    if(getColor(ptr) != oldColor){//Если ткнули на границу, выходим
        return;
    }
    spans.push(getSpan(x, y, bits, len));

    while(!spans.empty()){
    //for(int i = 0; i < 5; i++){
        Span current = spans.top();
        spans.pop();
        int left = current.getLeftX();

        //Закрашиваем спан
        ptr = &bits[4 * left + current.getY() * len];
        if (getColor(ptr) == oldColor){
            for (int i = left; i <= current.getRightX(); i++){
                ptr = &bits[4 * i + current.getY() * len];
                fillPixel(ptr, newColor);
            }
        }else if (getColor(ptr) == newColor) {
            continue;
        }

        //Идем вниз
        int startY = current.getY()+1;
        ptr = &bits[4 * left + startY * len];
        while (left <= current.getRightX()){//Добавляем спаны снизу пока не сравняли левую и правую границу
            while((getColor(ptr) != oldColor)&&(left <= current.getRightX())){//Пропускаем границу и уже закрашенные спаны
                left++;
                ptr = &bits[4 * left + startY * len];
            }
            if (left <= current.getRightX()){
                spans.push(getSpan(left, startY, bits, len));
            }
            left++;
        }

        //Идем наверх
        startY = current.getY()-1;
        left = current.getLeftX();
        ptr = &bits[4 * left + startY * len];
        while (left <= current.getRightX()){//Добавляем спаны снизу пока не сравняли левую и правую границу
            while((getColor(ptr) != oldColor)&&(left <= current.getRightX())){//Пропускаем границу и уже закрашенные спаны
                left++;
                ptr = &bits[4 * left + startY * len];
            }
            if (left <= current.getRightX()){
                spans.push(getSpan(left, startY, bits, len));
            }
            left++;
        }
    }
}

Span Painter::getSpan(int startX, int startY, unsigned char *bits, qint32 len){
    int X = startX;
    int Y = startY;
    int pos = 4 * X + Y * len;
    unsigned char *ptr = &bits[pos];
    while (isWhite(ptr)){
        X++;
        pos = 4 * X + Y * len;
        ptr = &bits[pos];
    }

    int right = X;
    X = startX;
    pos = 4 * startX + startY * len;
    ptr = &bits[pos];

    while (isWhite(ptr)){
        X--;
        pos = 4 * X + Y * len;
        ptr = &bits[pos];
    }
    int left = X;
    return Span(right - 1, left + 1, Y);
}

int Painter::getColor(unsigned char *ptr){
    if (ptr[0] == 0 && ptr[1] == 0 && ptr[2] == 0 && ptr[3] == 0){
        return WHITE;
    }
    if (ptr[0] == 0 && ptr[1] == 0 && ptr[2] == 0 && ptr[3] == 0xff){
        return BLACK;
    }
    if (ptr[0] == 0xff && ptr[1] == 0 && ptr[2] == 0 && ptr[3] == 0xff){
        return BLUE;
    }
}

bool Painter::isWhite(unsigned char *ptr){
    if (ptr[0] == 0 && ptr[1] == 0 && ptr[2] == 0 && ptr[3] == 0){
        return true;
    }
    return false;
}

void Painter::makeField(){
    int x = 0;
    int y = halfSize;
    bool even = false;
    for (int i = 0; i < N; i++){
        if (even){
            for (int j = 0; j < M; j++){
                Hexagon cur(x , y, cellSize, N, M);
                field.push_back(cur);
                x += 2 * halfSizeSqrt3;
            }
            x = 0;
            y += cellSize + halfSize;
        }else {
            for (int j = 0; j < M-1; j++){
                Hexagon cur(x , y, cellSize, N, M);
                field.push_back(cur);
                x += 2 * halfSizeSqrt3;
            }
            x = 0;
            y += cellSize + halfSize;
        }
        even = !even;
    }
}

Painter::~Painter(){}
