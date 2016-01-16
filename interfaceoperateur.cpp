#include "interfaceoperateur.h"
#include "ui_interfaceoperateur.h"
#include "global.hpp"
#include <stdio.h>
#include <QTime>
#include "commKoyo.h"
#include <iostream>

int joseph = 0;
int i;


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
        ++ joseph;
        refreshHMI->stop();
        refreshHMI->start();
        ui->Bassin2->setValue(bassin2Level);

        /* On verifie l'etat du flag (thread safe) et on attend 10 cycles que la variable soit initialisee par read ou write */
        /* Le stylesheet est applique sur chaque label (lumiere) */
        /* Attention ! dans le bitset, les bits sont a l'envers MSB -> LSB */
        if (koyo_int.flag == 0 && joseph>10) {
            koyo_int.flag = 1;

            if((*koyo_int.Outputs).test(15))
            {
                ui->out1->setStyleSheet("background: green; border : 2px solid; border-radius : 15px; border-color : white;");
            }
            else {
                ui->out1->setStyleSheet("background: black; border : 2px solid; border-radius : 15px; border-color : white;");
            }

            if((*koyo_int.Outputs).test(14))
            {
                ui->out2->setStyleSheet("background: green; border : 2px solid; border-radius : 15px; border-color : white;");
            }
            else {
                ui->out2->setStyleSheet("background: black; border : 2px solid; border-radius : 15px; border-color : white;");
            }

            if((*koyo_int.Outputs).test(13))
            {
                ui->out3->setStyleSheet("background: green; border : 2px solid; border-radius : 15px; border-color : white;");
            }
            else {
                ui->out3->setStyleSheet("background: black; border : 2px solid; border-radius : 15px; border-color : white;");
            }

            if((*koyo_int.Outputs).test(12))
            {
                ui->out4->setStyleSheet("background: green; border : 2px solid; border-radius : 15px; border-color : white;");
            }
            else {
                ui->out4->setStyleSheet("background: black; border : 2px solid; border-radius : 15px; border-color : white;");
            }

            if((*koyo_int.Outputs).test(11))
            {
                ui->out5->setStyleSheet("background: green; border : 2px solid; border-radius : 15px; border-color : white;");
            }
            else {
                ui->out5->setStyleSheet("background: black; border : 2px solid; border-radius : 15px; border-color : white;");
            }

            if((*koyo_int.Outputs).test(10))
            {
                ui->out6->setStyleSheet("background: green; border : 2px solid; border-radius : 15px; border-color : white;");
            }
            else {
                ui->out6->setStyleSheet("background: black; border : 2px solid; border-radius : 15px; border-color : white;");
            }

            std::cout << "Interface : " << (*koyo_int.Outputs) << "\n";
            for (i=0; i<17; ++i){
                std::cout << (*koyo_int.Outputs).test(i) << "-";
            }
            std::cout << "\n";
            koyo_int.flag = 0;
        }
        else {
            printf("Oops! Section critique : Petzi %i\n", joseph);
        }
    }
}

//ui->testkoyo->setText("Etat : " + QString::number((*koyo_int.Outputs));
//std::cout << "E/S : " << (*koyo.Inputs) << " | " << (*koyo.Outputs) << "\n";
