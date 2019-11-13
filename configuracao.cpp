#include "configuracao.h"
#include "ui_configuracao.h"
#include <QDebug>
#include <QtWidgets>


using namespace cv;
using namespace std;

configuracao::configuracao(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::configuracao)
{
    ui->setupUi(this);

    //Default object of lime color for test purposes, uncomment when needed.
    //objects.push_back(setUpObject("lime", 32,72, 105, 205, 18, 167));
    int Brilho = 60;
    int Exposure = -10;
    int Saturacao = 120;
    int Contraste = 200;
    //open capture object at location zero (default location for webcam)
    capture.open(0);
    //set height and width of capture frame
    capture.set(CV_CAP_PROP_CONTRAST  , Contraste);
    capture.set(CV_CAP_PROP_SATURATION, Saturacao);
    capture.set(CV_CAP_PROP_EXPOSURE  , Exposure);
    capture.set(CV_CAP_PROP_BRIGHTNESS, Brilho);
    capture.set(CV_CAP_PROP_FRAME_WIDTH, WIDTH);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, HEIGHT);
    //capture.set(CV_CAP_PROP_AUTOFOCUS, 0);

    namedWindow(imageWindow);
    namedWindow(hsvWindow);
    namedWindow(thresholdWindow);

    //To avoid windows stacking over each other,
    //these adjustmets could differ with screen sizes.
    moveWindow(imageWindow,0,0);
    moveWindow(hsvWindow, 600,0);
    moveWindow(thresholdWindow, 600,0);

    //novo objeto de Dialog
    //d = new Dialog();
    //c = new configuracao();



}

void configuracao::closeEvent(QCloseEvent *event)
{
    breakLoop=true;
    destroyAllWindows();
    //capture.~VideoCapture();
    this->destroy();
    event->accept();
}

configuracao::~configuracao()
{

    delete ui;
//    delete d;
//    delete c;
}

void configuracao::Start(){
    cout << "entrei em Start()" << endl;
    while (true){
        //Dialog *d = new Dialog d;
        if(breakLoop==true){
            return;
        }
        H_MIN = ui->hminBox->text().toInt();
        H_MAX = ui->hmaxBox->text().toInt();
        S_MIN = ui->sminBox->text().toInt();
        S_MAX = ui->smaxBox->text().toInt();
        V_MIN = ui->vminBox->text().toInt();
        V_MAX = ui->vmaxBox->text().toInt();
        int subtract1, subtract2;

        capture.read(cameraFeed);
        testObject.name=" ";
        cvtColor(cameraFeed,HSV, COLOR_BGR2HSV);
        inRange(HSV, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), testObject.threshold);
        morphObject(testObject.threshold);
        trackObject(x, y, testObject, cameraFeed);

        if (flag1 == 1) {
            for (unsigned int i = 0; i<player.size(); i++) {
                //QString s = QString::fromStdString(objects[i].name);
//                inRange(HSV, Scalar(objects[i].H_MIN, objects[i].S_MIN, objects[i].V_MIN), Scalar(objects[i].H_MAX, objects[i].S_MAX, objects[i].V_MAX), objects[i].threshold);
//                morphObject(objects[i].threshold);
//                trackObject(x, y, objects[i], cameraFeed);
                //qDebug() << "a subtracao foi" << (int)objects[i+1].x - (int)objects[0].x << "em object";
                if (objects[0].x - objects[i+1].x <= 100||objects[i+1].x - objects[0].x <= 100){
                    trackPlayer(player[i], HSV, cameraFeed, objects[0], objects[i+1]);
                    qDebug() << "Saiu! Amarelo em X:" << player[i].x << "e Y:" << player[i].y;
                    drawPlayer(player[i].x, player[i].y, player[i].flag, cameraFeed);
                }
               // qDebug() << "a subtracao foi" << objects[i+1].x - objects[0].x << "em object_adv";
                if (objects_adv[0].x - objects_adv[i+1].x <= 100||objects_adv[i+1].x - objects_adv[0].x <= 100){
                    trackPlayer(player_adv[i], HSV, cameraFeed, objects_adv[0], objects_adv[i+1]);
                    qDebug() << "Saiu! Azul em X_:" << player_adv[i].x << "e Y_:" << player_adv[i].y;
                    drawPlayer(player_adv[i].x, player_adv[i].y, player_adv[i].flag, cameraFeed);
                }
//                qDebug() << "Saiu! Amarelo em X:" << player[i].x << "e Y:" << player[i].y;
//                drawPlayer(player[i].x, player[i].y, player[i].flag, cameraFeed);

//                qDebug() << "Saiu! Azul em X_:" << player_adv[i].x << "e Y_:" << player_adv[i].y;
//                drawPlayer(player_adv[i].x, player_adv[i].y, player_adv[i].flag, cameraFeed);
               //qDebug() << "Cor: " << s.toLatin1() << " em X:" << x << "e Y:" << y;

            }
            //flag1 = 0;
            //qDebug() << "saiu.";
        } else {
            for (unsigned int i = 0; i<objects.size(); i++) {
                  //QString s = QString::fromStdString(objects[i].name);
                inRange(HSV, Scalar(objects[i].H_MIN, objects[i].S_MIN, objects[i].V_MIN), Scalar(objects[i].H_MAX, objects[i].S_MAX, objects[i].V_MAX), objects[i].threshold);
                morphObject(objects[i].threshold);
                trackObject(x, y, objects[i], cameraFeed);
                inRange(HSV, Scalar(ball.H_MIN, ball.S_MIN, ball.V_MIN), Scalar(ball.H_MAX, ball.S_MAX, ball.V_MAX), ball.threshold);
                morphObject(ball.threshold);
                trackObject(x, y, ball, cameraFeed);
                inRange(HSV, Scalar(objects_adv[i].H_MIN, objects_adv[i].S_MIN, objects_adv[i].V_MIN), Scalar(objects_adv[i].H_MAX, objects_adv[i].S_MAX, objects_adv[i].V_MAX), objects_adv[i].threshold);
                morphObject(objects_adv[i].threshold);
                trackObject(x, y, objects_adv[i], cameraFeed);

                //qDebug() << i << "X:" << objects[i].x << "Y:" << objects[i].y;
            }
        }

//        for (unsigned int i = 0; i<objects.size(); i++) {

//            inRange(HSV, Scalar(objects[i].H_MIN, objects[i].S_MIN, objects[i].V_MIN), Scalar(objects[i].H_MAX, objects[i].S_MAX, objects[i].V_MAX), objects[i].threshold);
//            morphObject(objects[i].threshold);
//            trackObject(x, y, objects[i], cameraFeed);

//            if(x <= 320)
//                flag = true;
//            else
//                flag = false;

//            if (flag == true && aux == false){
//               d->updateLED(QString("L%1")); //orienta LED a partir da coordenada X a ligar
//               aux = true;
//            }
//            if (flag == false && aux == true){
//                d->updateLED(QString("D%1")); //orienta LED a partir da coordenada X a desligar
//                aux = false;
//            }
//        }


        imshow(imageWindow, cameraFeed);
        imshow(hsvWindow, HSV);
        imshow(thresholdWindow,testObject.threshold);


        //delay 30ms so that screen can refresh.
        waitKey(30);
    }


}

string configuracao::numberToString(int number){


    std::stringstream ss;
    ss << number;
    return ss.str();
}

void configuracao::drawObject(int x, int y, Mat &frame, item tempItem){
    //qDebug() << "entrei aqui quarto";

    //rectangle(frame,Point(x-(sideLength/2),y-(sideLength/2)), Point(x+(sideLength/2),y+(sideLength/2)),Scalar(0,255,0),2);
    if (flag1 == 0)
        circle(frame,Point(x, y), sideLength/2,Scalar(0,255,0),2);
    else
        return;


    //drawContours(frame, contours, -1, (0,255,0), 3)
    //putText(frame, numberToString(x) + "," + numberToString(y), Point(x, y + 30), 1, 1, Scalar(0,72, 255), 1);
    putText(frame, tempItem.name , Point(x, y + 50), 2, 1, Scalar(0,72, 255), 1);
}

void configuracao::drawPlayer(int x, int y, bool time, Mat &frame){

    if (time == 0)
        circle(frame, Point(x,y), 40, Scalar(0,255,255),2);
    else
        circle(frame, Point(x,y), 40, Scalar(255,0,0),2);
}

void configuracao::morphObject(Mat &thresh){

    //qDebug() << "entrei aqui terceiro";

    //create structuring element that will be used to "dilate" and "erode" image.
    //the element chosen here is a 3px by 3px rectangle
    Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));

    //dilate with larger element so make sure object is nicely visible
    Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8));

    erode(thresh, thresh, erodeElement);
    erode(thresh, thresh, erodeElement);
    dilate(thresh, thresh, dilateElement);
    dilate(thresh, thresh, dilateElement);



}

void configuracao::trackObject(int &x, int &y, item &tempItem, Mat &cameraFeed){
    //qDebug() << "entrei aqui primeiro";
    Mat temp;
    tempItem.threshold.copyTo(temp);

    //these two vectors needed for output of findContours
    vector<vector<Point>> contours;
    //qDebug() << x << "," << y;
    vector<Vec4i> hierarchy;

    //find contours of filtered image using openCV findContours function
    findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, Point(0,0));

    //use moments method to find our filtered object
    double refArea = 0;
    bool objectFound = false;

    qDebug() << hierarchy.size();
    if (hierarchy.size() > 0) {
        int numObjects = hierarchy.size();
        //if number of objects greater than MAX_OBJECTS we have a noisy filter
       if (numObjects<MAX_OBJECTS){
            for (int index = 0; index >= 0; index = hierarchy[index][0]) {

                Moments moment = moments(contours[index]);
                area = moment.m00;
                //qDebug() << "Area: " << area;
                sideLength= sqrt(area);

                //if the area is less than 25 px by 25px then it is probably just noise
                //if the area is the same as the 1/2 of the image size, probably just a bad filter
                //we only want the object with the largest area so we safe a reference area each
                //iteration and compare it to the area in the next iteration.
               if (area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA) { // && area>refArea){
                    x = moment.m10 / area;
                    y = moment.m01 / area;
                    drawObject(x, y, cameraFeed, tempItem);
                    tempItem.x = x;
                    tempItem.y = y;
                    objectFound = true;
                    refArea = area;


                }
                else objectFound = false;


            }
            //let user know you found an object
           // if (objectFound == true){
                //draw object location on screen
             //   drawObject(x, y, cameraFeed, tempItem);


            //}

      }
   }
}

void configuracao::trackPlayer (jogador &tempJogador, Mat &HSV, Mat &cameraFeed, item color1, item color2){

    int x_aux[2];
    int y_aux[2];

    inRange(HSV, Scalar(color1.H_MIN, color1.S_MIN, color1.V_MIN), Scalar(color1.H_MAX, color1.S_MAX, color1.V_MAX), color1.threshold);
    morphObject(color1.threshold);
    trackObject(x_aux[0], y_aux[0], color1, cameraFeed);
    qDebug() << QString::fromStdString(color1.name) << "Xcolor1:" << x_aux[0] << "Ycolor1:" << y_aux[0];



    inRange(HSV, Scalar(color2.H_MIN, color2.S_MIN, color2.V_MIN), Scalar(color2.H_MAX, color2.S_MAX, color2.V_MAX), color2.threshold);
    morphObject(color2.threshold);
    trackObject(x_aux[1], y_aux[1], color2, cameraFeed);
    qDebug() << QString::fromStdString(color2.name) << "Xcolor2:" << x_aux[1] << "Ycolor2:" << y_aux[1];


    qDebug() << "dentro da funcao é " << x_aux[0] - x_aux[1];
    if (x_aux[0] - x_aux[1] <= 100){
    tempJogador.x = (x_aux[0] + x_aux[1])/2;
    tempJogador.y = (y_aux[0] + y_aux[1])/2;
    }
//    if (color1.H_MIN <= 148)
//        tempJogador.flag = 0;
//    else
//        tempJogador.flag = 1;

    //qDebug() << "Xplayer:" << tempJogador.x << "Yplayer:" << tempJogador.y;

}

configuracao::item configuracao::setUpObject(string name, int hmin, int hmax, int smin, int smax, int vmin, int vmax){

    item temp;
    temp.name = name;
    //temp.x = x;
    //temp.y = y;
    temp.H_MIN = hmin;
    temp.H_MAX = hmax;
    temp.S_MIN = smin;
    temp.S_MAX = smax;
    temp.V_MIN = vmin;
    temp.V_MAX = vmax;

    return temp;

}

configuracao::jogador configuracao:: setUpPlayer(bool flag,int number){

    jogador temp;

    temp.flag = flag;
    //temp.x = x;
    //temp.y = y;
    //temp.angle = angle;
    temp.number = number;


    return temp;

}

void configuracao::on_addButton_clicked()
{
//    objects.push_back(setUpObject(ui->nameLineEdit->text().toStdString(),H_MIN,H_MAX,S_MIN,S_MAX,V_MIN,V_MAX));
//    ui->nameLineEdit->clear();

//    ui->hminBox->setValue(0);
//    ui->hmaxBox->setValue(255);
//    ui->sminBox->setValue(0);
//    ui->smaxBox->setValue(255);
//    ui->vminBox->setValue(0);
//    ui->vmaxBox->setValue(255);
//    i += 1;

    QString Azul = "Azul";
    QString Amarelo = "Amarelo";
    QString Bola = "Bola";


    if(ui->comboBox->currentText() == Azul){
    objects.push_back(setUpObject(ui->nameLineEdit->text().toStdString(),H_MIN,H_MAX,S_MIN,S_MAX,V_MIN,V_MAX));
    ui->nameLineEdit->clear();

    ui->hminBox->setValue(0);
    ui->hmaxBox->setValue(255);
    ui->sminBox->setValue(0);
    ui->smaxBox->setValue(255);
    ui->vminBox->setValue(0);
    ui->vmaxBox->setValue(255);
    i += 1;
    }

    if(ui->comboBox->currentText() == Amarelo){
    objects_adv.push_back(setUpObject(ui->nameLineEdit->text().toStdString(),H_MIN,H_MAX,S_MIN,S_MAX,V_MIN,V_MAX));
    ui->nameLineEdit->clear();

    ui->hminBox->setValue(0);
    ui->hmaxBox->setValue(255);
    ui->sminBox->setValue(0);
    ui->smaxBox->setValue(255);
    ui->vminBox->setValue(0);
    ui->vmaxBox->setValue(255);
    i += 1;
    }

    if(ui->comboBox->currentText() == Bola){
        ball = setUpObject(ui->nameLineEdit->text().toStdString(),H_MIN,H_MAX,S_MIN,S_MAX,V_MIN,V_MAX);

        ui->nameLineEdit->clear();

        ui->hminBox->setValue(0);
        ui->hmaxBox->setValue(255);
        ui->sminBox->setValue(0);
        ui->smaxBox->setValue(255);
        ui->vminBox->setValue(0);
        ui->vmaxBox->setValue(255);
        i += 1;
    }

}

void configuracao::on_defaultButton_clicked()
{
    ui->hminBox->setValue(0);
    ui->hmaxBox->setValue(255);
    ui->sminBox->setValue(0);
    ui->smaxBox->setValue(255);
    ui->vminBox->setValue(0);
    ui->vmaxBox->setValue(255);

    flag1 = 0;

}

void configuracao::on_pushButton_clicked()
{
    QString Azul = "Azul";
    QString Amarelo = "Amarelo";
    if (i >= 2) {
        flag1 = 1;
    if(objects_adv.size() > 0) {
    player_adv.push_back(setUpPlayer(0,j));

    j += 1;
    }
    if(objects.size() > 0) {
    player.push_back(setUpPlayer(1,k));

    k += 1;
    }
    }
    QMessageBox::warning(this, "Aviso","O Jogador foi criado!");

}

void configuracao::on_pushButton_2_clicked()
{
    if (flag1 == true) {
        flag1 = false;
    } else {
        flag1 = true;
    }

}

void configuracao::on_pushButton_3_clicked()
{
    capture.set(CV_CAP_PROP_SETTINGS, 0);
}
