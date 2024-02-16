#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <iostream>
#include <fstream>
#include <ctunes.h>
#include <genero.h>
#include <QMessageBox>>
Ctunes ctunes;
genero enumGenero;
using std::string;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_AddSong_pressed()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_AgregarCancionBt_pressed()
{
    std::string NombreSong = ui->NombreCancion->text().toStdString();
    std::string nombreCantante = ui->NombreCantante->text().toStdString();
    //std::string GeneroMusical = ui->Genero->text().toStdString();
    std::string duracion = ui->Duracion->text().toStdString();
    std::string GeneroMusical=ui-> genero->currentText().toStdString();
    // Convert string to enum
    if (GeneroMusical == "POP") {
        enumGenero = POP;
    } else if (GeneroMusical == "ROCK") {
        enumGenero = ROCK;
    } else if (GeneroMusical == "RAP") {
        enumGenero = RAP;
    } else if (GeneroMusical == "DANCE") {
        enumGenero = DANCE;
    } else if (GeneroMusical == "REGGAE") {
        enumGenero = REGGAE;
    } else if (GeneroMusical == "ELECTRONICA") {
        enumGenero = ELECTRONICA;
    } else if (GeneroMusical == "RANCHERA") {
        enumGenero = RANCHERA;
    }

    double precioSong = ui->Precio->text().toDouble();

      ctunes.addSong(NombreSong, nombreCantante, enumGenero, precioSong,duracion);
    std::cout<<"termino";
    ui->stackedWidget->setCurrentIndex(0);
}



void MainWindow::on_pushButtonGuardar_pressed()
{
    int code = ui->CODESONG->text().toInt();
    int stars = ui->CantStars->text().toInt();
    if(ctunes.reviewSong(code,stars)){
         QMessageBox:: information(this,"Guardado",QString(QString:: fromStdString("Se guardo Correctamente")));
    }else {
        QMessageBox:: information(this,"OPS...",QString(QString:: fromStdString("Algo salio mal")));
    }
     ui->stackedWidget->setCurrentIndex (0) ;
}


void MainWindow::on_pushButton_pressed()
{
     ui->stackedWidget->setCurrentIndex (0) ;
}


void MainWindow::on_DownloadSong_pressed()
{
     ui->stackedWidget->setCurrentIndex (2) ;
}


void MainWindow::on_pushButton_2_pressed()
{
     ui->stackedWidget->setCurrentIndex (0) ;
}


void MainWindow::on_pushButton_3_pressed()
{
    int code = ui->codigoSong->text().toInt();
    QString info = QString:: fromStdString(ctunes.infoSong(code));
    ui->Texto->setText(info);
}


void MainWindow::on_Songs_pressed()
{
     ui->stackedWidget->setCurrentIndex (1) ;
}


void MainWindow::on_ReviewSong_pressed()
{
     ui->stackedWidget->setCurrentIndex (3) ;
}


void MainWindow::on_InfoSongs_pressed()
{
     ui->stackedWidget->setCurrentIndex (5) ;
}


void MainWindow::on_pushButton_4_pressed()
{
    exit(0);
}


void MainWindow::on_pushButton_5_pressed()
{
    ui->stackedWidget->setCurrentIndex (0);
}


void MainWindow::on_BuyButton_6_pressed()
{
    int code = ui->CodigoDeCancion->text().toInt();
    std::string NombreCliente = ui->NombreCliente->text().toStdString();
    QMessageBox:: information(this,"hello",QString(QString:: fromStdString(ctunes.downloadSong(code,NombreCliente))));

}


void MainWindow::on_pushButton_6_pressed()
{
    std::string nombretxt = ui->Nametext->text().toStdString();
    QString info = QString:: fromStdString(ctunes.songs(nombretxt));
    ui->SongsText->setText(info);
}

