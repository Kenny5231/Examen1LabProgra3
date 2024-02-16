#include "ctunes.h"
//para los archivos
#include <QFile>
#include <QDataStream>
#include <QDate>
#include <QTextStream>
//convierto son en ese archivo
QFile Songs("/Users/Kenny/Proyects_Pragra3/ExamenProgra3Lab/songs.itn");
QFile Codigo("/Users/Kenny/Proyects_Pragra3/ExamenProgra3Lab/codigo.itn");
QFile Download("/Users/Kenny/Proyects_Pragra3/ExamenProgra3Lab/Download.itn");
//templete

template<class TipoD>
double hacer(TipoD num){
    double numero= num;
    return num;
}

//para leer
QDataStream write (&Songs);
QDataStream read (&Songs);
QDataStream code (&Codigo);
QDataStream download(&Download);
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

void Ctunes::addSong(std::string nombre, std::string cantante, genero generoCantante, double precio,    std::string duracion) {
    Formato p;
        //int code = 0;
        //QString cancion =" ";
        //QString  nombreCantante = " ";
        //genero generoMusical;
        //double precioDownload = 0.0;
        //int estrellas = 0;
        //int reviews = 0;
        //int raiting = 0;
        //QString Duracion=" ";
    //en caso de cambiar el download debo de pasarlo a 4
    p.code=getCodigo(0);
    p.cancion = QString:: fromStdString(nombre);
    p.nombreCantante = QString:: fromStdString(cantante);
    p.generoMusical = generoCantante;
    p.precioDownload = precio;
    p.estrellas = 0;
    p.reviews = 0;
    p.raiting = 0;
    p.Duracion= QString:: fromStdString(duracion);
    Songs.seek(Songs.size());
    write << p.code<<p.cancion<<p.nombreCantante<<p.generoMusical<<p.precioDownload<<p.estrellas<<p.reviews<<p.raiting<< p.Duracion;
    Songs.flush();
}
bool Ctunes::reviewSong(int code, int stars)
{
    Songs.seek(0);
    while (!Songs.atEnd()) {
        long seek = Songs.pos();
        Formato cancion;
        read >> cancion.code >> cancion.cancion >> cancion.nombreCantante >> cancion.generoMusical >> cancion.precioDownload >> cancion.estrellas >> cancion.reviews >> cancion.raiting>> cancion.Duracion;
        if (cancion.code == code) {
            int newreviews = cancion.reviews + 1;
            int newstars = cancion.estrellas + stars;
            double estrellas= hacer<int>(newstars);
            double vistas=hacer<int>(newreviews);
            double rating= estrellas/vistas;
            Songs.seek(seek);
            write << cancion.code << cancion.cancion << cancion.nombreCantante << cancion.generoMusical << cancion.precioDownload << newstars << newreviews << rating << cancion.Duracion;
            Songs.flush();
            return true;
        }
    }
    return false;
}
string Ctunes::downloadSong(int codeSong, string cliente)
{
    Songs.seek(0);
    while(!Songs.atEnd()){
        Formato cancion;
        read>>cancion.code>>cancion.cancion>>cancion.nombreCantante>>cancion.generoMusical>>cancion.precioDownload>>cancion.estrellas>>cancion.reviews>>cancion.raiting>> cancion.Duracion;
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
    string info="";
    QString direccion= "/Users/Kenny/Proyects_Pragra3/ExamenProgra3Lab/"+QString::fromStdString(txtFile)+".txt";
    QFile archivotxt (direccion);
    QTextStream escritura(&archivotxt);
    archivotxt.open(QIODevice::ReadWrite);
    archivotxt.resize(0);
    Songs.seek(0);

    Formato Song;
    while(!Songs.atEnd()){
        //CODIGO – TITULO – CANTANTE – DURACION – PRECIO – RATING
        read>>Song.code>>Song.cancion>>Song.nombreCantante>>Song.generoMusical>>Song.precioDownload>>Song.estrellas>>Song.reviews>>Song.raiting>>Song.Duracion;
        escritura <<"CODIGO: "<< Song.code<<" - TITULO: " << Song.cancion <<" - CANTANTE: "<< Song.nombreCantante <<" - DURACION: "<< Song.Duracion <<" - PRECIO: "<< Song.precioDownload <<" - RATING: "<< Song.raiting<<".\n" ;
        info+="CODIGO:"+QString::number(Song.code).toStdString()+" - TITULO:" + Song.cancion.toStdString()+" - CANTANTE: "+ Song.nombreCantante.toStdString() +" - DURACION: "+ Song.Duracion.toStdString() +" - PRECIO: "+QString::number(Song.precioDownload).toStdString()  +" - RATING: "+QString::number(Song.raiting).toStdString() +".\n" ;
    }

    return info;
}

string Ctunes::infoSong(int codeSong)
{
    Songs.seek(0);
    while(!Songs.atEnd()){
        Formato Song;
        read>>Song.code>>Song.cancion>>Song.nombreCantante>>Song.generoMusical>>Song.precioDownload>>Song.estrellas>>Song.reviews>>Song.raiting>>Song.Duracion;
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
            int veces=0;
            string InfoDownload="";
            Download.seek(0);
            while(!Download.atEnd()){
                //int codigoDownloads;
                //string fecha;
                //int codeSongDownloads;
                //string clienteDoDownloads;
                //double songDownloads;
                FormatoDownloads format;
                QString fechaString, clienteString;
                download >> format.codigoDownloads >> fechaString >> format.codeSongDownloads >> clienteString >> format.songDownloads;
                format.fecha = fechaString.toStdString();
                format.clienteDoDownloads = clienteString.toStdString();
                if(format.codeSongDownloads==codeSong){
                    veces++;
                    InfoDownload+="Codigo de descarga: "+ QString::number(format.codigoDownloads).toStdString()  +", Fecha de descarga: "+format.fecha +", Codigo de cancion: "+QString::number(format.codeSongDownloads).toStdString()+", Cliente: "+format.clienteDoDownloads+", Precio: "+QString::number(format.songDownloads).toStdString()+"\n";
                }
            }
            //Song.raiting= Song.estrellas/Song.reviews;
            return "Godigo: "+QString::number(Song.code).toStdString() +", Nombre de Cancion: "+Song.cancion.toStdString() +", Nombre de Cantante: "+Song.nombreCantante.toStdString()+"\nDuracion: "+Song.Duracion.toStdString()+", Genero: "
                   +genero1+", Precio Download: "+QString::number(Song.precioDownload).toStdString()+", Estrellas: "+QString::number(Song.estrellas).toStdString()+",\nRaiting: "+QString::number(Song.raiting).toStdString()+", Cantidad de reviews: "+QString::number(Song.reviews).toStdString()+" Veces descargada: "+QString::number(veces).toStdString()+" \nInformacion: \n"+InfoDownload;
        }
    }
    return"No existe dicho codigo.";
}
