#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent = nullptr);
    ~OptionsDialog();

signals:
    void MChanged(int);
    void NChanged(int);
    void cellSizeChanged(int);
    void modeChanged(bool);


public slots:
    void connectCellSlider(QString);
    void connectCellSize(int);

private slots:
    void on_pushButton_clicked();

private:
    Ui::OptionsDialog *ui;
};

#endif // OPTIONSDIALOG_H
