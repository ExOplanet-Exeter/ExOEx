#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configure.h"
#include <QDesktopServices>
#include <QUrl>
#include <QTimer>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("ExOEx - Protostar Build");

    // ASK TIM ABOUT THIS. SHOULD BE SOME BETTER WAY TO GRAB PATH
    chdir("/Users/FreddyWordingham/Desktop/ExOEx/Arc/");

    QPixmap picture("sap.png");
    ui->label_picture->setPixmap(picture);

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_run_clicked()
{
    QString filename = "/Users/FreddyWordingham/Desktop/ExOEx/Arc/arc";
    QDesktopServices::openUrl(QUrl("file:///"+filename,QUrl::TolerantMode));

    return;
}

void MainWindow::on_pushButton_configure_clicked()
{
    Configure configure;
    configure.setModal(true);
    configure.exec();
}

void MainWindow::showTime(){
    QTime time = QTime::currentTime();

    QString time_text = time.toString("hh : mm : ss");

    if ((time.msec() / 500) < 1){
        time_text[3] = ' ';
        time_text[8] = ' ';
    }

    ui->label_clock->setText(time_text);

    return;
}
