#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "painter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    //void resizeEvent(QResizeEvent *);
    ~MainWindow();

private slots:
    void on_action_triggered();

    void on_actionSet_Options_triggered();

    void on_actionXOR_triggered();

private:
    Ui::MainWindow *ui;
    QPixmap me;
    Painter *painter;
};

#endif // MAINWINDOW_H
