#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QWidget>
#include "painter.h"

class Controller : public QWidget
{
    Q_OBJECT

private:
    Painter *painter;
public:
    Controller(QWidget *parent, Painter *p);

private slots:
   void ChangeM();
};

#endif // CONTROLLER_H
