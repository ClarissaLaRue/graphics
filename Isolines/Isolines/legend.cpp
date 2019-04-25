#include <QImage>
#include <iostream>
#include <QPainter>
#include "legend.h"

legend::legend(QWidget *parent) : QWidget(parent)
{

}

void legend::addColors(int n, vector<QColor> colors){
    this->n = n;
    this->colors = colors;
}


void legend::paintEvent(QPaintEvent *){
    draw();
}

void legend::draw(){
    QPainter p(this);
    QPoint start(0, 0);
    int startLegend = 20;
    int cell = 30;
    QImage image(size(), QImage::Format_ARGB32);
    unsigned char *bits = image.bits();
    qint32 len = image.bytesPerLine();

    for (int i = 0 ; i < n; i++){
        QRect rect(startLegend + cell*i, startLegend , cell, cell);
        p.drawRect(rect);
        QRect rect2(startLegend + cell*i + 1, startLegend+ 1, cell - 1 , cell - 1 );
        p.fillRect(rect2, colors[i]);
    }

    p.drawImage(start, image);
}


