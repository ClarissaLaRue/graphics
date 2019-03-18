#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "optionsdialog.h"
#include <iostream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    painter(new Painter(this)),
    options(new OptionsDialog())
{
    ui->setupUi(this);
    ui->scrollArea->setWidget(painter);
    //Изменение параметров M, N, cellSize через диалоговое окно
    connect(&options, SIGNAL(MChanged(int)), this, SLOT(setMChanged(int)));
    connect(&options, SIGNAL(NChanged(int)), this, SLOT(setNChanged(int)));
    connect(&options, SIGNAL(cellSizeChanged(int)), this, SLOT(setCellSizeChanged(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::resizeEvent(QResizeEvent *) {
//    ui->scrollArea->setMaximumSize(ui->centralWidget->size());
//    ui->scrollArea->setMinimumSize(ui->centralWidget->size());
//}


//Информация о разработчике
void MainWindow::on_action_triggered()
{
    QMessageBox *info = new QMessageBox();
    info->setWindowTitle("Info about Korobova Anastasya");
    info->setText("FIT Korobova 16209");
    QPixmap pixmap;
    pixmap.load(":/me2.jpg");
    info->setIconPixmap(pixmap);
    info->exec();
}

//Окно диалога настройки игры
void MainWindow::on_actionSet_Options_triggered()
{
    //OptionsDialog options;
    options.setFixedSize(400, 400);
    options.setModal(true);
    options.exec();

}

//Функции для изменения параметров М, N, size при изменении их в диалоговом окне options
void MainWindow::setMChanged(int M){
    painter->setM(M);
}

void MainWindow::setNChanged(int N){
    painter->setN(N);
}

void MainWindow::setCellSizeChanged(int size){
    painter->setSize(size);
}

void MainWindow::on_actionXOR_triggered()
{

}
