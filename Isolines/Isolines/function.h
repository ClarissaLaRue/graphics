#ifndef FUNCTION_H
#define FUNCTION_H


class Function
{
public:
    Function();
    float calculate(int x, int y);
    void findMaxMin(int a, int b, int c, int d);
    float getMax();
    float getMin();

private:
    float min;
    float max;
};

#endif // FUNCTION_H
