#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "configuracao.h"
#include "constantes_campo.h"
#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    constantes_campo *constantes;
    configuracao *c;
    bool criou_objeto = false; //método que inicializará a classe configuração.

    explicit MainWindow(QWidget *parent = 0); // Construtor.
    void closeEvent (QCloseEvent *event); //Método para quando o botão close for clicado.

    ~MainWindow(); //Destrutor.

private slots:
    void on_pushButton_clicked();

    void on_actionCarregar_Arquivos_triggered();

    void update_window();

    void mousePressEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;

    QTimer *timer;
    cv::VideoCapture cap;

    cv::Mat frame;
    QImage qt_image;


};

#endif // MAINWINDOW_H
