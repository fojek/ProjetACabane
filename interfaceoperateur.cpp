#include "interfaceoperateur.h"
#include "ui_interfaceoperateur.h"
#include "global.hpp"
#include <stdio.h>
#include <QTime>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <commKoyo.h>
#include <QtSql>
#include <QtDebug>
#include <QMutex>
#include <QtCore>
#include <iostream>
#include <string>

using namespace std;

int joseph = 0;
int i;
int koyoCMDupdate;
int koyoCMDupdateGraph;
int koyoCMD[8];
int entreeKoyo[8];
int sortieKoyo[8];
int premierScan = 1;

QSqlDatabase db = QSqlDatabase::addDatabase( "QMYSQL" );

/* On retrouve l'addresse du singleton Koyo */
Koyo & koyo_int=Koyo::Instance();

/* Création de l'instance du GUI */
InterfaceOperateur::InterfaceOperateur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InterfaceOperateur)
{
    ui->setupUi(this);

    qRegisterMetaType<SQLRES>("SQLRES");

    Worker *worker = new Worker;
    worker->moveToThread(&workerThread);
    connect(&workerThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(this, SIGNAL(operate(QString)), worker, SLOT(doWork(void)));
    connect(worker, SIGNAL(resultReady(SQLRES)), this, SLOT(handleResults(SQLRES)));
    workerThread.start();

	/* Timer pour le scan time de l'interface. 50ms? */
    refreshHMI = new QTimer(this);
    refreshHMI->setInterval(2000);
    timerCount = 0;

    /* Timer pour les requêtes SQL */
    timerSQL = new QTimer(this);
    timerSQL->setInterval(1);
    timerSQLcount = 0;
	
    /* Création du timer refresh */
    connect(refreshHMI, SIGNAL(timeout()), this, SLOT(timerTimeout()));

    /* Création du timer SQL */
    connect(timerSQL, SIGNAL(timeout()), this, SLOT(timerSQLTimeout()));

    refreshHMI->start();
    timerSQL->start();

    /* Initialisation des graphiques */
    ui->qcp->addGraph();
    ui->qcp->addGraph();

    ui->qcp->xAxis->setLabel("Temps");
    ui->qcp->yAxis->setLabel("Temperature");
    ui->qcp->graph(0)->setPen(QPen(Qt::blue));
    ui->qcp->graph(0)->setName("Temperature");

    ui->qcp->graph(1)->setPen(QPen(Qt::red));
    ui->qcp->graph(1)->setName("Pression");

    ui->qcp->legend->setVisible(true);
    ui->qcp->legend->setFont(QFont("Helvetica",9));
}

/* Destructeur */
InterfaceOperateur::~InterfaceOperateur()
{
    db.close();
    workerThread.quit();
    delete &workerThread;
    delete ui;
}

/* Requête SQL */
void InterfaceOperateur::timerSQLTimeout()
{
    --timerSQLcount;
    if (timerSQLcount <= 0)
    {
        if (db.isOpen()) {
            emit operate("Stuff");
            timerSQL->stop();
            timerSQL->start();
        }
    }
}

/* Événement de rafraîchissement de l'interface */
void InterfaceOperateur::timerTimeout()
{
    --timerCount;
    if (timerCount <= 0)
    {
        /* Tab Graphiques

        query_state=mysql_query(connection, "select temperature from temperature order by temps desc limit 100");

        if(query_state!=0){
          std::cout<<mysql_error(connection)<<std::endl<<std::endl;
        }

        res=mysql_store_result(connection);

        QVector<double> x(101), y(101);
        for (int i=100; i>0; --i)
        {
          x[i] = i;
          if ((row=mysql_fetch_row(res)) != NULL){
              y[i] = atof(row[0]);
          }
          else {
              y[i]=0;
          }
        }

        QVector<double> x2(101), y2(101);
        for (int i=0; i<101; ++i)
        {
          x2[i] = i;
          y2[i] = cos(x[i]*50) * 20;
        }

        ui->qcp->graph(0)->setData(x, y);
        ui->qcp->graph(1)->setData(x2, y2);

        ui->qcp->rescaleAxes();

        ui->qcp->replot();

        /***** STATUS ****/

        ++ joseph;
        refreshHMI->stop();
        refreshHMI->start();

        /* On verifie l'etat du flag (thread safe) et on attend 10 cycles que la variable soit initialisee par read ou write */
        /* Le stylesheet est applique sur chaque label (lumiere) */
        if (koyo_int.flag == 0 && joseph>10) {
            koyo_int.flag = 1;

            /* Outputs */
            if((*koyo_int.Outputs).test(0))
            {
                ui->out1->setStyleSheet("background: green; border : 2px solid; border-radius : 15px; border-color : white;");
            }
            else {
                ui->out1->setStyleSheet("background: black; border : 2px solid; border-radius : 15px; border-color : white;");
            }

            if((*koyo_int.Outputs).test(1))
            {
                ui->out2->setStyleSheet("background: green; border : 2px solid; border-radius : 15px; border-color : white;");
            }
            else {
                ui->out2->setStyleSheet("background: black; border : 2px solid; border-radius : 15px; border-color : white;");
            }

            if((*koyo_int.Outputs).test(2))
            {
                ui->out3->setStyleSheet("background: green; border : 2px solid; border-radius : 15px; border-color : white;");
            }
            else {
                ui->out3->setStyleSheet("background: black; border : 2px solid; border-radius : 15px; border-color : white;");
            }

            if((*koyo_int.Outputs).test(3))
            {
                ui->out4->setStyleSheet("background: green; border : 2px solid; border-radius : 15px; border-color : white;");
            }
            else {
                ui->out4->setStyleSheet("background: black; border : 2px solid; border-radius : 15px; border-color : white;");
            }

            if((*koyo_int.Outputs).test(4))
            {
                ui->out5->setStyleSheet("background: green; border : 2px solid; border-radius : 15px; border-color : white;");
            }
            else {
                ui->out5->setStyleSheet("background: black; border : 2px solid; border-radius : 15px; border-color : white;");
            }

            if((*koyo_int.Outputs).test(5))
            {
                ui->out6->setStyleSheet("background: green; border : 2px solid; border-radius : 15px; border-color : white;");
            }
            else {
                ui->out6->setStyleSheet("background: black; border : 2px solid; border-radius : 15px; border-color : white;");
            }

            /* Inputs */
            if((*koyo_int.Inputs).test(0))
            {
                ui->in1->setStyleSheet("background: green; border : 2px solid; border-radius : 15px; border-color : white;");
            }
            else {
                ui->in1->setStyleSheet("background: black; border : 2px solid; border-radius : 15px; border-color : white;");
            }

            if((*koyo_int.Inputs).test(1))
            {
                ui->in2->setStyleSheet("background: green; border : 2px solid; border-radius : 15px; border-color : white;");
            }
            else {
                ui->in2->setStyleSheet("background: black; border : 2px solid; border-radius : 15px; border-color : white;");
            }

            if((*koyo_int.Inputs).test(2))
            {
                ui->in3->setStyleSheet("background: green; border : 2px solid; border-radius : 15px; border-color : white;");
            }
            else {
                ui->in3->setStyleSheet("background: black; border : 2px solid; border-radius : 15px; border-color : white;");
            }

            if((*koyo_int.Inputs).test(3))
            {
                ui->in4->setStyleSheet("background: green; border : 2px solid; border-radius : 15px; border-color : white;");
            }
            else {
                ui->in4->setStyleSheet("background: black; border : 2px solid; border-radius : 15px; border-color : white;");
            }

            if((*koyo_int.Inputs).test(4))
            {
                ui->in5->setStyleSheet("background: green; border : 2px solid; border-radius : 15px; border-color : white;");
            }
            else {
                ui->in5->setStyleSheet("background: black; border : 2px solid; border-radius : 15px; border-color : white;");
            }

            if((*koyo_int.Inputs).test(5))
            {
                ui->in6->setStyleSheet("background: green; border : 2px solid; border-radius : 15px; border-color : white;");
            }
            else {
                ui->in6->setStyleSheet("background: black; border : 2px solid; border-radius : 15px; border-color : white;");
            }

            koyo_int.flag = 0;
        }
        else {
            printf("C++ : Interface : Erreur code Petzi %i\n", joseph);
        }
    }
}

//ui->testkoyo->setText("Etat : " + QString::number((*koyo_int.Outputs));
//std::cout << "E/S : " << (*koyo.Inputs) << " | " << (*koyo.Outputs) << "\n";

void InterfaceOperateur::on_outsw_1_valueChanged(int value)
{
    if(ui->outsw_1->value()) { (*koyo_int.Outputs_buffer).set(0); }
    else { (*koyo_int.Outputs_buffer).reset(0); }

    std::cout << "######### C++ : Interface : " << (*koyo_int.Outputs) << " | " << (*koyo_int.Outputs_buffer) << "\n";
}

void InterfaceOperateur::on_outsw_2_valueChanged(int value)
{

    if(ui->outsw_2->value()) { (*koyo_int.Outputs_buffer).set(1); }
    else { (*koyo_int.Outputs_buffer).reset(1); }

    std::cout << "######### C++ : Interface : " << (*koyo_int.Outputs) << " | " << (*koyo_int.Outputs_buffer) << "\n";
}

void InterfaceOperateur::handleResults(SQLRES sqlres) {

    qDebug() << "Received";

    ui->TemperatureDehors->display(sqlres.temp);
    ui->PressionTubulure->display(sqlres.press);
    ui->Bassin1->setValue(sqlres.bassin1);
    ui->Bassin2->setValue(sqlres.bassin2);

    if(entreeKoyo[0]) {
        ui->textePompe1->setStyleSheet("QLabel { background-color : green; }");
        ui->textePompe1->setText("En marche");
    }
    else{
        ui->textePompe1->setStyleSheet("QLabel { background-color : red; }");
        ui->textePompe1->setText("Arrêté");

    }
    if(entreeKoyo[1]) {
        ui->textePompe2->setStyleSheet("QLabel { background-color : green; }");
        ui->textePompe2->setText("En marche");
    }
    else{
        ui->textePompe2->setStyleSheet("QLabel { background-color : red; }");
        ui->textePompe2->setText("Arrêté");
    }
    if(sortieKoyo[4]) {
        ui->texteVidange1->setStyleSheet("QLabel { background-color : green; }");
        ui->texteVidange1->setText("En marche");
    }
    else{
        ui->texteVidange1->setStyleSheet("QLabel { background-color : red; }");
        ui->texteVidange1->setText("Arrêté");
    }
    if(sortieKoyo[5]) {
        ui->texteVidange2->setStyleSheet("QLabel { background-color : green; }");
        ui->texteVidange2->setText("En marche");
    }
    else{
        ui->texteVidange2->setStyleSheet("QLabel { background-color : red; }");
        ui->texteVidange2->setText("Arrêté");
    }
    if(entreeKoyo[4]) {
        ui->texteTransvideur1->setStyleSheet("QLabel { background-color : green; }");
        ui->texteTransvideur1->setText("En marche");
    }
    else{
        ui->texteTransvideur1->setStyleSheet("QLabel { background-color : red; }");
        ui->texteTransvideur1->setText("Arrêté");
    }
    if(entreeKoyo[5]) {
        ui->texteTransvideur2->setStyleSheet("QLabel { background-color : green; }");
        ui->texteTransvideur2->setText("En marche");
    }
    else{
        ui->texteTransvideur2->setStyleSheet("QLabel { background-color : red; }");
        ui->texteTransvideur2->setText("Arrêté");
    }

    if(koyoCMDupdateGraph!=0){
        ui->marcheVidange1->setStyleSheet("background-color: rgb(240, 240, 240);");
        ui->arretVidange1->setStyleSheet("background-color: rgb(240, 240, 240);");
        ui->marcheVidange2->setStyleSheet("background-color: rgb(240, 240, 240);");
        ui->arretVidange2->setStyleSheet("background-color: rgb(240, 240, 240);");
        koyoCMDupdateGraph = 0;
    }
}

void Worker::doWork() {

    QSqlQuery qry_dw;
    SQLRES sqlres;

    qry_dw.prepare( "SELECT * FROM `cabaneDB`.`Koyo_Sorties_CMD`" );
    if( !qry_dw.exec() )
      qDebug() << qry_dw.lastError();
    else
    {
      QSqlRecord rec = qry_dw.record();

      qry_dw.next();

      for(i=0; i<8; ++i){
        sortieKoyo[i] = qry_dw.value(i+1).toInt();
      }
    }

    /* Pour éviter que les sorties soient "écrasées" lors d'une reconnection */
    if(premierScan){
        for(i=0; i<8; ++i){
          koyoCMD[i] = sortieKoyo[i];
        }
        premierScan = 0;
    }

    /* Scan pour savoir quelle entrée doit être updatée. */
    if(koyoCMDupdate == 1) {
        qry_dw.prepare("UPDATE `cabaneDB`.`Koyo_Sorties_CMD` SET Out0=:val0, Out1=:val1, Out2=:val2, Out3=:val3, Out4=:val4, Out5=:val5, Out6=:val6, Out7=:val7");
        qry_dw.bindValue(":val0", koyoCMD[0]);
        qry_dw.bindValue(":val1", koyoCMD[1]);
        qry_dw.bindValue(":val2", koyoCMD[2]);
        qry_dw.bindValue(":val3", koyoCMD[3]);
        qry_dw.bindValue(":val4", koyoCMD[4]);
        qry_dw.bindValue(":val5", koyoCMD[5]);
        qry_dw.bindValue(":val6", koyoCMD[6]);
        qry_dw.bindValue(":val7", koyoCMD[7]);

        if(!qry_dw.exec()) {
            qDebug() << qry_dw.lastQuery() << i;
            qDebug() << qry_dw.lastError();
        }
        else {
            koyoCMDupdate = 0;
            koyoCMDupdateGraph = 1;
        }
    }

    qDebug( "Data ..." );
    qry_dw.prepare( "SELECT Temperature, Pression, Bassin1, Bassin2 FROM Data ORDER BY Temps DESC LIMIT 1" );
    if( !qry_dw.exec() )
      qDebug() << qry_dw.lastError();
    else
    {
      qDebug( "Data done." );
      QSqlRecord rec = qry_dw.record();

      qry_dw.next();
      sqlres.temp = qry_dw.value(0).toDouble();
      sqlres.press = qry_dw.value(1).toDouble();
      sqlres.bassin1 = qry_dw.value(2).toDouble();
      sqlres.bassin2 = qry_dw.value(3).toDouble();
    }

    qry_dw.prepare( "SELECT * FROM `cabaneDB`.`Koyo_Entrees`" );
    if( !qry_dw.exec() )
      qDebug() << qry_dw.lastError();
    else
    {
      QSqlRecord rec = qry_dw.record();

      qry_dw.next();

      for(i=0; i<8; ++i){

        entreeKoyo[i] = qry_dw.value(i+1).toInt();
      }
    }

    Sleep(1000);
    emit resultReady(sqlres);
}

void InterfaceOperateur::on_boutonConnexion_clicked()
{
    /* Connection a la BDD */

    db.setHostName( ui->texteAdresse->text());
    db.setDatabaseName( "cabaneDB" );
    db.setPort(ui->textePort->text().toInt());

    db.setUserName("admin");
    db.setPassword("cabane");

    if( !db.open() )
    {
      qDebug() << db.lastError();
      ui->TexteConnexion->setText("Échec de la connexion.");
    }
    else {
      qDebug("Connected!");
      ui->TexteConnexion->setText("Connexion réussie!");
    }

}

/*
void InterfaceOperateur::on_pushButton_6_clicked()
{
    ui->Pompe3Statut->setStyleSheet("QLabel { background-color : green; }");
    ui->Pompe3Statut->setText("En marche");
}

void InterfaceOperateur::on_pushButton_5_clicked()
{
    ui->Pompe3Statut->setStyleSheet("QLabel { background-color : red; }");
    ui->Pompe3Statut->setText("Arret");
}
*/

void InterfaceOperateur::on_startPompe1_clicked()
{
    if(koyoCMD[0] == 0){
        koyoCMD[0] = 1;
        ui->startPompe1->setStyleSheet("background-color: rgb(0, 85, 255);");
    }
    else{
        koyoCMD[0] = 0;
        ui->startPompe1->setStyleSheet("background-color: rgb(240, 240, 240);");
    }
    koyoCMDupdate = 1;

}

void InterfaceOperateur::on_arretPompe1_clicked()
{
    if(koyoCMD[1] == 0){
        koyoCMD[1] = 1;
        ui->arretPompe1->setStyleSheet("background-color: rgb(0, 85, 255);");
    }
    else{
        koyoCMD[1] = 0;
        ui->arretPompe1->setStyleSheet("background-color: rgb(240, 240, 240);");
    }
    koyoCMDupdate = 1;
}

void InterfaceOperateur::on_marchePompe1_clicked()
{
    if(koyoCMD[2] == 0){
        koyoCMD[2] = 1;
        ui->marchePompe1->setStyleSheet("background-color: rgb(0, 85, 255);");
    }
    else{
        koyoCMD[2] = 0;
        ui->marchePompe1->setStyleSheet("background-color: rgb(240, 240, 240);");
    }
    koyoCMDupdate = 1;
}

void InterfaceOperateur::on_arretPompe2_clicked()
{
    if(koyoCMD[3] == 0){
        koyoCMD[3] = 1;
        ui->arretPompe2->setStyleSheet("background-color: rgb(0, 85, 255);");
    }
    else{
        koyoCMD[3] = 0;
        ui->arretPompe2->setStyleSheet("background-color: rgb(240, 240, 240);");
    }
    koyoCMDupdate = 1;
}

void InterfaceOperateur::on_marcheVidange1_clicked()
{
    koyoCMD[4] = 1;
    koyoCMDupdate = 1;
    ui->marcheVidange1->setStyleSheet("background-color: rgb(0, 85, 255);");
}

void InterfaceOperateur::on_arretVidange1_clicked()
{
    koyoCMD[4] = 0;
    koyoCMDupdate = 1;
    ui->arretVidange1->setStyleSheet("background-color: rgb(0, 85, 255);");
}

void InterfaceOperateur::on_marcheVidange2_clicked()
{
    koyoCMD[5] = 1;
    koyoCMDupdate = 1;
    ui->marcheVidange2->setStyleSheet("background-color: rgb(0, 85, 255);");
}

void InterfaceOperateur::on_arretVidange2_clicked()
{
    koyoCMD[5] = 0;
    koyoCMDupdate = 1;
    ui->arretVidange2->setStyleSheet("background-color: rgb(0, 85, 255);");
}
