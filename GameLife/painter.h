#ifndef PAINTER_H
#define PAINTER_H
#include "hexagon.h"

#include <QWidget>
#include <vector>
#include <list>
#include "span.h"

using std::list;
using std::vector;

class Painter : public QWidget
{
    Q_OBJECT
public:
    explicit Painter(QWidget *parent = nullptr);
    void setM(int M);
    void setN(int N);
    void setSize(int size);
    void makeField();
    void fillPixel(unsigned char *pix, int color);
    bool isWhite(unsigned char *pix);
    void drawAscendingLine(int x0, int y0, int x1, int y1, unsigned char *bits, qint32 len);
    void drawDescendingLine(int x0, int y0, int x1, int y1, unsigned char *bits, qint32 len);
    void drawVerticalLine(int x0, int y0, int x1, int y1, unsigned char *bits, qint32 len);
    void drawHexagon(int x, int y, unsigned char *bits, qint32 len);
    void drawHexagonLine(int x, int y, unsigned char *bits, qint32 len, int M);
    void drawField(unsigned char *bits, qint32 len);
    void span(int x, int y, unsigned char *bits, qint32 len,int oldColor, int newColor);
    Span getSpan(int x, int y, unsigned char *bits, qint32 len);
    int getColor(unsigned char *bits);
    int getColor(Span span);
    ~Painter();

protected:
    void paintEvent(QPaintEvent *);
    //void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    //void wheelEvent(QWheelEvent *e);

signals:
    void pressMouse(int x, int y);

private slots:
    void draw(QPainter &p);

private:
    QImage image;
    unsigned char *bits;
    qint32 len;
    int cellSize = 90;
    int halfSize;
    int halfSizeSqrt3;
    int M = 3;
    int N = 3;
    list<Hexagon> field;
    const int BLACK = 0;
    const int BLUE = 1;
    const int WHITE = 2;

};

#endif // PAINTER_H
