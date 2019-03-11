#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "optionsdialog.h"
#include <iostream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    //painter(new Painter(this))
{
    ui->setupUi(this);
    ui->scrollArea->setWidget(painter);
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
    OptionsDialog options;
    options.setFixedSize(400, 485);
    options.setModal(true);
    options.exec();

}

void MainWindow::on_actionXOR_triggered()
{

}
