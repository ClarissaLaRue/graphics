#ifndef PAINTER_H
#define PAINTER_H
#include <QWidget>
#include <vector>

using std::vector;

class Painter : public QWidget
{
    Q_OBJECT
public:
    explicit Painter(QWidget *parent = nullptr);
    Painter(QWidget *parent, int x, int y);
    void fillPixforLine(int x, int y, unsigned char *bits, qint32 len);
    void drawAscendingLine(int x0, int y0, int x1, int y1, unsigned char *bits, qint32 len);
    void drawDescendingLine(int x0, int y0, int x1, int y1, unsigned char *bits, qint32 len);
    void drawVerticalLine(int x0, int y0, int x1, int y1, unsigned char *bits, qint32 len);
    void drawHexagon(int x, int y, int cellSize, int halfSize, int halfSizeSqrt3, unsigned char *bits, qint32 len);
    void drawHexagonLine(int x, int y, int cellSize, int halfSize, int halfSizeSqrt3, unsigned char *bits, qint32 len, int M);
    void drawField(int cellSize, int halfSize, int halfSizeSqrt3, unsigned char *bits, qint32 len, int M, int N);
    void span(unsigned char *bits, qint32 len);
    ~Painter();

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);

private slots:
    void draw(QPainter &p);

private:
    char **image;
};

#endif // PAINTER_H
