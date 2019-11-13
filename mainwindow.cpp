#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    timer = new QTimer(this);

    //c = new configuracao();

    cap.open(0);


    if(!cap.isOpened())  // Check if we succeeded
    {
        cout << "camera is not open" << endl;
    }
    else
    {
        cout << "camera is open" << endl;
        //cap.set(CV_CAP_PROP_SETTINGS, 0);

//        cap.set(CV_CAP_PROP_BRIGHTNESS, brilho);


//        cap.set(CV_CAP_PROP_CONTRAST  , contraste);

//        cap.set(CV_CAP_PROP_EXPOSURE  , exposicao);

//        cap.set(CV_CAP_PROP_SATURATION, saturacao);

//        cap.set(CV_CAP_PROP_FOCUS, focus);

        //cap.set(CV_CAP_PROP_SETTINGS, 0);

        connect(timer, SIGNAL(timeout()), this, SLOT(update_window()));
        timer->start(20);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
    delete c;
    delete constantes;
}

void MainWindow::on_pushButton_clicked()
{
    if (criou_objeto == false){
        c = new configuracao();
        constantes = new constantes_campo();
        criou_objeto = true;
    }

    c->show();
    c->breakLoop = false;
    c->Start();

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    destroyAllWindows();
    this->destroy();
    event->accept();
    c->closeEvent(event);
    c->capture.~VideoCapture();
    cap.~VideoCapture();
}

void MainWindow::on_actionCarregar_Arquivos_triggered()
{
    c->capture.open(0);
    c->capture.set(CV_CAP_PROP_CONTRAST  , 0);
    c->capture.set(CV_CAP_PROP_SATURATION, 0);
    c->capture.set(CV_CAP_PROP_EXPOSURE  , 0);
    c->capture.set(CV_CAP_PROP_BRIGHTNESS, 0);
}

void MainWindow::update_window()
{
    cap >> frame;

    cvtColor(frame, frame, CV_BGR2RGB);

    qt_image = QImage((const unsigned char*) (frame.data), frame.cols, frame.rows, QImage::Format_RGB888);

    ui->label->setPixmap(QPixmap::fromImage(qt_image));

    ui->label->resize(ui->label->pixmap()->size());
}

void MainWindow::mousePressEvent(QMouseEvent *event) {

    constantes->mousePressEvent(event);

}
