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
