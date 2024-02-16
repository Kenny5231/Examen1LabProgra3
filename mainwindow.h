#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//

//
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //void on_pushButton_clicked();

  //  void on_AddSong_clicked();

    void on_AddSong_pressed();

    void on_AgregarCancionBt_pressed();

    void on_pushButtonGuardar_pressed();

    void on_pushButton_pressed();

    void on_DownloadSong_pressed();

    void on_pushButton_2_pressed();

    void on_pushButton_3_pressed();

    void on_Songs_pressed();

    void on_ReviewSong_pressed();

    void on_InfoSongs_pressed();

    void on_pushButton_4_pressed();

    void on_pushButton_5_pressed();

    void on_BuyButton_6_pressed();

    void on_pushButton_6_pressed();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
