#ifndef INTERFACEOPERATEUR_H
#define INTERFACEOPERATEUR_H

#define TRIG 2
#define ECHO 3

#include <QMainWindow>
#include <QtGui>
#include "lib\QCustomPlot\qcustomplot.h"
#include <QtCore>
#include <QtSQL>

typedef struct {
    double temp;
    double press;
    double bassin1;
    double bassin2;
} SQLRES;

Q_DECLARE_METATYPE(SQLRES);

namespace Ui {
class InterfaceOperateur;
}

class InterfaceOperateur : public QMainWindow
{
    Q_OBJECT
    QThread workerThread;

public:
    explicit InterfaceOperateur(QWidget *parent = 0);
    ~InterfaceOperateur();

public slots:
    void handleResults(SQLRES sqlres);

private slots:

    void timerTimeout();

    void timerSQLTimeout();

    void on_outsw_1_valueChanged(int value);

    void on_outsw_2_valueChanged(int value);

    void on_boutonConnexion_clicked();

    void on_marcheVidange1_clicked();

    void on_arretVidange1_clicked();

    void on_marcheVidange2_clicked();

    void on_arretVidange2_clicked();

    void on_startPompe1_clicked();

    void on_arretPompe1_clicked();

    void on_marchePompe1_clicked();

    void on_arretPompe2_clicked();

private:
    Ui::InterfaceOperateur *ui;
    QTimer *refreshHMI;
    QTimer *timerSQL;
    int timerCount;
    int timerSQLcount;
signals:
    void operate(const QString &);
};


class Worker : public QObject
{
    Q_OBJECT
    QThread workerThread;

public slots:
    void doWork();

signals:
    void resultReady(const SQLRES &sqlres);
};

#endif // INTERFACEOPERATEUR_H
