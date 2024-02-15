#include "ctunes.h"
//para los archivos
#include <QFile>
#include <QDataStream>
#include <QDate>
//
//convierto son en ese archivo
QFile Songs("/Users/Kenny/Proyects_Pragra3/ExamenProgra3Lab/songs.itn");
QFile Codigo("/Users/Kenny/Proyects_Pragra3/ExamenProgra3Lab/codigo.itn");
QFile Download("/Users/Kenny/Proyects_Pragra3/ExamenProgra3Lab/Download.itn");
//para leer
QDataStream write (&Songs);
QDataStream read (&Songs);
QDataStream code (&Codigo);
QDataStream download(&Download);
//
Ctunes::Ctunes() {
    Songs.open(QIODevice::ReadWrite);
    Codigo.open(QIODevice::ReadWrite);
    Download.open(QIODevice::ReadWrite);
    if(!Songs.isOpen()){
        exit(0);
    }
    if(!Codigo.isOpen()){
        exit(0);
    }
    if(!Download.isOpen()){
        exit(0);
    }
    if(Codigo.size()==0){
        code<<1;
        Codigo.seek(Codigo.size());
        code<<1;
    }
}

int Ctunes::getCodigo(long offset) {
    Codigo.seek(offset);
    int tempo;
    code>>tempo;
    Codigo.seek(offset);
    int mas= tempo+1;
    code<<mas;
    return tempo;
}

void Ctunes::addSong(std::string nombre, std::string cantante, genero generoCantante, double precio) {
    Formato p;
    //en caso de cambiar el download debo de pasarlo a 4
    p.code=getCodigo(0);
    p.cancion = QString:: fromStdString(nombre);
    p.nombreCantante = QString:: fromStdString(cantante);
    p.generoMusical = generoCantante;
    p.precioDownload = precio;
    p.estrellas = 0;
    p.reviews = 0;
    p.raiting = 0;
    Songs.seek(Songs.size());
    write << p.code<<p.cancion<<p.nombreCantante<<p.generoMusical<<p.precioDownload<<p.estrellas<<p.reviews<<p.raiting;
    Songs.flush();
}

string Ctunes::downloadSong(int codeSong, string cliente)
{
    Songs.seek(0);
    while(!Songs.atEnd()){
        Formato cancion;
        read>>cancion.code>>cancion.cancion>>cancion.nombreCantante>>cancion.generoMusical>>cancion.precioDownload>>cancion.estrellas>>cancion.reviews>>cancion.raiting;
        string genero1;
        if (cancion.code==codeSong){
            FormatoDownloads downloads;
            //int codigoDownloads;
            //string fecha;
            //int codeSongDownloads;
            //string clienteDoDownloads;
            //double songDownloads;
            downloads.codigoDownloads=getCodigo(4);
            QDate Datestart = QDate::currentDate();
            QString stringDate = Datestart.toString("dd-MM-yyyy");
            downloads.fecha=stringDate.toStdString();
            downloads.codeSongDownloads=cancion.code;
            downloads.clienteDoDownloads=cliente;
            downloads.songDownloads= cancion.precioDownload;
            //falta subir a el archivo
            Download.seek(Download.size());
            download << downloads.codigoDownloads  <<  QString::fromStdString(downloads.fecha)  <<  downloads.codeSongDownloads  <<  QString::fromStdString(downloads.clienteDoDownloads)  <<  downloads.songDownloads;
            Download.flush();
            return"GRACIAS["+cliente+"] por bajar ["+cancion.cancion.toStdString()+"] a un costo de Lps. ["+ QString::number(cancion.precioDownload).toStdString()+ "]";
        }
    }
    return"No existe";
}

std::string Ctunes::songs(std::string txtFile) {
    return "";
}

string Ctunes::infoSong(int codeSong)
{
    Songs.seek(0);
    while(!Songs.atEnd()){
        Formato Song;
        read>>Song.code>>Song.cancion>>Song.nombreCantante>>Song.generoMusical>>Song.precioDownload>>Song.estrellas>>Song.reviews>>Song.raiting;
        string genero1;
        if (Song.generoMusical == POP) {
            genero1 = "POP";
        } else if (Song.generoMusical == ROCK) {
            genero1 = "ROCK";
        } else if (Song.generoMusical == RAP) {
            genero1 = "RAP";
        } else if (Song.generoMusical == DANCE) {
            genero1 = "DANCE";
        } else if (Song.generoMusical == REGGAE) {
            genero1 = "REGGAE";
        } else if (Song.generoMusical == ELECTRONICA) {
            genero1 = "ELECTRONICA";
        } else if (Song.generoMusical == RANCHERA) {
            genero1 = "RANCHERA";
        }
        if (Song.code==codeSong){
            return "Godigo: "+QString::number(Song.code).toStdString() +", Nombre de Cancion: "+Song.cancion.toStdString() +", Nombre Cantante: "+Song.nombreCantante.toStdString()+", Genero: "
                   +genero1+", Precio Download: "+QString::number(Song.precioDownload).toStdString()+", Estrellas: "+QString::number(Song.estrellas).toStdString()+", Raiting: "+QString::number(Song.raiting).toStdString();
        }
    }
    return"No existe dicho codigo.";
}
