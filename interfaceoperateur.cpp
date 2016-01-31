#include "interfaceoperateur.h"
#include "ui_interfaceoperateur.h"
#include "global.hpp"
#include <stdio.h>
#include <QTime>
#include "commKoyo.h"
#include <iostream>
#include <mysql/mysql.h>
#include <iomanip>
#include <fstream>

int joseph = 0;
int i;

/* Connection SQL */
MYSQL *connection, mysql;
MYSQL_RES *res;
MYSQL_ROW row;
int query_state,a;

/* On retrouve l'addresse du singleton Koyo */
Koyo & koyo_int=Koyo::Instance();

/* Création de l'instance du GUI */
InterfaceOperateur::InterfaceOperateur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InterfaceOperateur)
{
    ui->setupUi(this);
	/* Timer pour le scan time de l'interface. 50ms? */
    refreshHMI = new QTimer(this);
    refreshHMI->setInterval(50);
    timerCount = 0;
	
	/* Création du timer */
    connect(refreshHMI, SIGNAL(timeout()), this, SLOT(timerTimeout()));
	
	/* On force le style graphique du GUI */
    QApplication::setStyle(new QPlastiqueStyle);
    refreshHMI->start();

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

    /* Connection a la BDD */
    mysql_init(&mysql);
    connection = mysql_real_connect(&mysql,"localhost","root","cabane", "cabaneDB",0,0,0);
    if(connection==NULL) std::cout << mysql_error(&mysql) << std::endl;

}

/* Destructeur */
InterfaceOperateur::~InterfaceOperateur()
{
    delete ui;
}

void InterfaceOperateur::on_pushButton_6_clicked()
{
    ui->Pompe3Statut->setStyleSheet("QLabel { background-color : green; }");
    ui->Pompe3Statut->setText("En marche");
    digitalWrite (0, HIGH) ;
}

void InterfaceOperateur::on_pushButton_5_clicked()
{
    ui->Pompe3Statut->setStyleSheet("QLabel { background-color : red; }");
    ui->Pompe3Statut->setText("Arret");
    digitalWrite (0,  LOW) ;
}

void InterfaceOperateur::on_pushButton_10_clicked()
{ 
}

void InterfaceOperateur::on_pushButton_9_clicked()
{
    printf("State : %i\n", digitalRead(ECHO));
}

/* Événement de rafraîchissement de l'interface */
void InterfaceOperateur::timerTimeout()
{
    --timerCount;
    if (timerCount <= 0)
    {
        /* Tab Graphiques */

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
        ui->Bassin2->setValue(bassin2Level);

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

void InterfaceOperateur::on_pushButton_3_clicked()
{

}
