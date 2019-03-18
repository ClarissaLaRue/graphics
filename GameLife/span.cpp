#include "span.h"

Span::Span(int x, int y){
    rightX = x;
    leftX = x;
    Y = y;
}

Span::Span(int x1, int x2, int y){
    rightX = x1;
    leftX = x2;
    Y = y;
}

int Span::getRightX(){
    return rightX;
}

int Span::getLeftX(){
    return leftX;
}

int Span::getY(){
    return Y;
}

int Span::getColor(){
    return color;
}
