#include "function.h"
#include <math.h>

Function::Function()
{

}

float Function::calculate(float x, float y){
    //return x + y;
    //return (x * x) - (y * y);
    return sin((float)x/100) * sin((float)y/100);
    //return x*x*x + y*y;
}

void Function::findMaxMin(int a, int b, int c, int d){
    min = calculate(a, c);
    max = calculate(a, c);
    float tmp;
    for(int i = a; i <= b; i++){
        for (int j = c; j <= d; j++){
            tmp = calculate(i, j);
            if (tmp < min){
                min = tmp;
            }
            if( tmp > max){
                max = tmp;
            }
        }
    }
}

float Function::getMax(){
    return max;
}

float Function::getMin(){
    return min;
}
