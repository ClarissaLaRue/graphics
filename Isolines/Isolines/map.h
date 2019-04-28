#ifndef MAP_H
#define MAP_H

#include "configuration.h"
#include "function.h"

#include <QObject>
#include <QWidget>
#include <QPaintEvent>

using std::pair;


class Map: public QWidget
{
    Q_OBJECT
public:
    explicit Map(QWidget *parent = nullptr);
    void addConfig(configuration config);
    void draw();
    void fillPix(unsigned char *ptr, QColor color);
    void findColorRange();
    void grid();
    void isolines();
    void point();
    QColor chooseColor(float f);

    struct Colors{
        float from;
        float to;
        QColor color;
    };

private:
    void drawIsolines(QPainter &p);
    void drawGrid(unsigned char *bits, qint32 len);
    void drawVerticalLine(int x0, int y0, int x1, int y1, unsigned char *bits, qint32 len);
    void drawHorizontalLine(int x0, int y0, int x1, int y1, unsigned char *bits, qint32 len);
    void findingPoints(int x, int y, int stepX, int stepY, float z);

protected:
    void paintEvent(QPaintEvent *);

private:
    configuration config;
    vector<Colors> colors;
    vector<pair<int, int>> inPoint;
    float min;
    float max;
    bool needLsolines = true;
    bool needGrid = false;
    bool needPoint = true;
};

#endif // MAP_H
