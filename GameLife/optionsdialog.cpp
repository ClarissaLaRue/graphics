#include "optionsdialog.h"
#include "ui_optionsdialog.h"
#include <iostream>
#include <QIntValidator>

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
    ui->lineM->setValidator(new QIntValidator(0,99 ,this));
    ui->lineN->setValidator(new QIntValidator(0,99 ,this));
    ui->cellSize->setValidator(new QIntValidator(0,99,this));
    //связка слайдер-поле
    connect(ui->cellSize, SIGNAL(textChanged(QString)), this, SLOT(connectCellSlider(QString)));
    connect(ui->cellSlider, SIGNAL(valueChanged(int)), this, SLOT(connectCellSize(int)));
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

void OptionsDialog::connectCellSlider(QString size){
    ui->cellSlider->setValue(size.toInt());
}

void OptionsDialog::connectCellSize(int size){
    ui->cellSize->setText(QString::number(size));
}


//отправляем данные при нажатии кнопки Create
void OptionsDialog::on_pushButton_clicked()
{
    emit(MChanged(ui->lineM->text().toInt()));
    emit(NChanged(ui->lineN->text().toInt()));
    emit(cellSizeChanged(ui->cellSlider->value()));
    emit(modeChanged(ui->XOR));
    this->close();
}
