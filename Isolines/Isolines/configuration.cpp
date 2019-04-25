#include "configuration.h"

configuration::configuration()
{

}

configuration::configuration(int k, int m, int n, vector<QColor> colors, QColor lineColor){
    this->k = k;
    this->m = m;
    this->n = n;
    this->colors = colors;
    this->lineColor = lineColor;
}

void configuration::setK(int k){
    this->k = k;
}

void configuration::setM(int m){
    this->m = m;
}

void configuration::setN(int n){
    this->n = n;
}

void configuration::setDomain(int a, int b, int c, int d){
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
}

void configuration::setColors(vector<QColor> colors){
    this->colors = colors;
}

void configuration::setLineColor(QColor lineColor){
    this->lineColor = lineColor;
}

int configuration::getK(){
    return k;
}

int configuration::getM(){
    return m;
}

int configuration::getN(){
    return  n;
}

vector<QColor> configuration::getColors(){
    return colors;
}

int configuration::getA(){
    return a;
}

int configuration::getB(){
    return b;
}

int configuration::getC(){
    return c;
}

int configuration::getD(){
    return d;
}

void configuration::setFunction(Function function){
    this->function = function;
}

Function configuration::getFunction(){
    return function;
}

void configuration::findMaxMin(int a, int b, int c, int d){
    return function.findMaxMin(a, b, c, d);
}

float configuration::getMin(){
    return function.getMin();
}

float configuration::getMax(){
    return function.getMax();
}

float configuration::calculate(int x, int y){
    return function.calculate(x, y);
}

QColor configuration::getLineColor(){
    return lineColor;
}
