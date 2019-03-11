#include "controller.h"

Controller::Controller(QWidget *parent, Painter *p)
{
    painter = p;
    connect(painter, SIGNAL(MChanged(int)), this, SLOT(ChangeM()));
}

void Controller::ChangeM(){

}
