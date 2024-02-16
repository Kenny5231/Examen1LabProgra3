#ifndef CTUNES_H
#define CTUNES_H
// para usar el string de la libreria
#include <string>
//para llamar una clase externa
#include <genero.h>
#include <QString>
// declarar string de la libreria standart
using namespace std;
class Ctunes
{
    struct Formato{
        int code = 0;
        QString cancion =" ";
        QString  nombreCantante = " ";
        genero generoMusical;
        double precioDownload = 0.0;
        int estrellas = 0;
        int reviews = 0;
        double raiting = 0;
        QString Duracion=" ";
    };
    struct FormatoDownloads{
        int codigoDownloads;
        string fecha;
        int codeSongDownloads;
        string clienteDoDownloads;
        double songDownloads;
    };
//genero genero;
public:
    Ctunes();
    int getCodigo(long offset);
    void addSong(string nombre, string cantante, genero generoCantante, double precio, std::string duracion);
    bool reviewSong(int code, int stars);
    string downloadSong(int codeSong, string cliente);
    string songs(string txtFile);
    string infoSong(int codeSong);
};

#endif // CTUNES_H
