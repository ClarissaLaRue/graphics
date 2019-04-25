#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    parser()
{
    ui->setupUi(this);
    configuration config = makeConfig();
    ui->legendWidget->addColors(config.getN(), config.getColors());
    ui->mapWidget->addConfig(config);
    ui->legendWidget->repaint();
    ui->mapWidget->repaint();

}

MainWindow::~MainWindow()
{
    delete ui;
}

//Выбор файла
void MainWindow::on_actionOpen_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, "Open file", "C://");
    parser.ParseFile(file);

}

//Дефолтная конфигурация для цветов
configuration MainWindow::makeConfig(){
    vector<QColor> colors;
    colors.push_back(QColor(255, 0 , 0));
    colors.push_back(QColor(255, 0 , 180));
    colors.push_back(QColor(200, 0 , 255));
    colors.push_back(QColor(40, 0 , 255));
    colors.push_back(QColor(0, 200 , 255));
    configuration config(5, 5, 5, colors, QColor(0, 0, 0));
    config.findMaxMin(config.getA(),config.getB(), config.getC(), config.getD());
    return config;
}

void MainWindow::on_actionGrid_triggered()
{
    ui->mapWidget->grid();
}

void MainWindow::on_actionPoint_mode_triggered()
{
    ui->mapWidget->point();
}

void MainWindow::on_actionIsolines_ON_OFF_triggered()
{
    ui->mapWidget->isolines();
}
