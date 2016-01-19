#ifndef INTERFACEOPERATEUR_H
#define INTERFACEOPERATEUR_H

#define TRIG 2
#define ECHO 3

#include <QMainWindow>
#include <QtGui>

#include <wiringPi.h>

namespace Ui {
class InterfaceOperateur;
}

class InterfaceOperateur : public QMainWindow
{
    Q_OBJECT

public:
    explicit InterfaceOperateur(QWidget *parent = 0);
    ~InterfaceOperateur();

private slots:
    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_9_clicked();

    void timerTimeout();

    void on_outsw_1_valueChanged(int value);

    void on_outsw_2_valueChanged(int value);

private:
    Ui::InterfaceOperateur *ui;
    QTimer *refreshHMI;
    int timerCount;
};

#endif // INTERFACEOPERATEUR_H
