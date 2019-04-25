#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "legend.h"
#include "parser.h"
#include "configuration.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    configuration makeConfig();
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionGrid_triggered();

    void on_actionPoint_mode_triggered();

    void on_actionIsolines_ON_OFF_triggered();

private:
    Ui::MainWindow *ui;
    Parser parser;
};

#endif // MAINWINDOW_H
