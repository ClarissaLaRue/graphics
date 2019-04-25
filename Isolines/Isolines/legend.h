#ifndef LEGEND_H
#define LEGEND_H

#include <QObject>
#include <QWidget>
#include <QColor>
#include <QString>
#include <vector>

using std::vector;

class legend: public QWidget
{
    Q_OBJECT
public:
    explicit legend(QWidget *parent = nullptr);
    void addColors(int n, vector<QColor> colors);
    void draw();

protected:
    void paintEvent(QPaintEvent *);

private:
    int n = 5;
    vector<QColor> colors;
    QColor black = QColor(0, 0, 0);
};

#endif // LEGEND_H
