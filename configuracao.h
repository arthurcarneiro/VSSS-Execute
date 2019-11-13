#ifndef CONFIGURACAO_H
#define CONFIGURACAO_H

#include "opencv2/opencv.hpp"
#include <iostream>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QMouseEvent>
#include <QDialog>
#include <cstdlib>
#include <windows.h>
#include <QMainWindow>
#include <QCloseEvent>
#include <sstream>
#include <string>
#include <iostream>
#include <thread>
#include <opencv\highgui.h>
#include <opencv\cv.h>
#include <opencv2\opencv.hpp>


using namespace cv;
using namespace std;

namespace Ui {
class configuracao;
}

class configuracao : public QDialog
{
    Q_OBJECT

public:
    //Variables to hold HSV values. (HSV = HUE, SATURATION and VALUE)
    int H_MIN, H_MAX, S_MIN, S_MAX, V_MIN, V_MAX;

    // Area and Sides of Threshold Contour
    double area;
    double sideLength;

    const int BOLA = 0;
    const int COMPANHEIRO = 1;
    const int ADVERSARIO = 2;

    //capture frame width and height
    const int WIDTH = 640;
    const int HEIGHT = 480;

    //max number of objects to be tracked in frame
    static const int MAX_OBJECTS = 6;

    //minimum and maximum object area
    const int MIN_OBJECT_AREA = 15 * 15;
    const int MAX_OBJECT_AREA = HEIGHT*WIDTH / 2;

    //names that appear at the top of each window
    const std::string imageWindow = "Original Image";
    const std::string hsvWindow = "HSV Image";
    const std::string thresholdWindow = "Thresholded Image";
    bool breakLoop=false;

    //Matrix to store each frame of the webcam feed
    cv::Mat cameraFeed;

    //matrix storage for HSV image
    cv::Mat HSV;
    int x = 0, y = 0;
    cv::VideoCapture capture;

    int i = 0;
    int j = 0; //contador de jogador de um time
    int k = 0; //contador de jogador do adversário

    //Struct to define the attributes of the objects to be tracked.
    typedef struct {
        std::string name;
        int x;
        int y;
        int H_MIN= H_MIN;
        int H_MAX = H_MAX;
        int S_MIN= S_MIN;
        int S_MAX= S_MAX;
        int V_MIN= V_MIN;
        int V_MAX= V_MAX;
        cv::Mat threshold;
    }item ;

    typedef struct {
        //std::string time;
        bool flag; // 0 para adversário, 1 para meu time
        int x;
        int y;
        int number;
        float angle;
        cv::Mat threshold;
    } jogador;

    // Dynamic object who's attributes (specifically HSV) can be changed in real time.
    item testObject;

    // To store objects with defined values.
    std::vector<item> objects;
    std::vector<item> objects_adv;
    item ball;

    // To store players with defined values.
    std::vector<jogador> player;
    std::vector<jogador> player_adv;

    // To access the elements of Dialog and configuracao
    //Dialog *d;
    //configuracao *c;

    //bools pra testar os leds
    bool flag = false;
    bool aux = false;

    //bool pra testar as cores
    bool flag1 = 0;

    explicit configuracao(QWidget *parent = 0);
    void closeEvent (QCloseEvent *event);
    std::string numberToString(int number);
    void Start();
    void drawObject(int x, int y, cv::Mat &frame, item tempItem);
    void morphObject(cv::Mat &thresh);
    void trackObject(int &x, int &y, item &tempItem, cv::Mat &cameraFeed);
    void trackPlayer (jogador &tempJogador, cv::Mat &HSV, cv::Mat &cameraFeed, item color1, item color2);
    void drawPlayer(int x, int y, bool time, cv::Mat &frame);
    jogador setUpPlayer(bool flag, int number);
    item setUpObject(std::string name, int hmin, int hmax, int smin, int smax, int vmin, int vmax);

     ~configuracao();

private slots:

    void on_addButton_clicked();

    void on_defaultButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::configuracao *ui;
};


#endif // CONFIGURACAO_H
