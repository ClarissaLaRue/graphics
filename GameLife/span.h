#ifndef SPAN_H
#define SPAN_H


class Span
{
public:
    Span(int x, int y);
    Span(int x1, int x2, int y);
    int getRightX();
    int getLeftX();
    int getY();
    int getColor();

private:
    int rightX;
    int leftX;
    int Y;
    int color;
};

#endif // SPAN_H
