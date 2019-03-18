#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "optionsdialog.h"
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

public slots:
    void on_actionClear_triggered();
signals:
    void MChanged(int M);
    void NChanged(int N);
    void cellSizeChanged(int);

private slots:
    void on_action_triggered();
    void on_actionSet_Options_triggered();
    void on_actionXOR_triggered();
    void setMChanged(int M);
    void setNChanged(int N);
    void setCellSizeChanged(int);

private:
    Ui::MainWindow *ui;
    QPixmap me;
    Painter *painter;
    OptionsDialog options;
};

#endif // MAINWINDOW_H
