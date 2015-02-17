#include "mainwindow.h"
#include "ui_mainwindow.h"

// Printing to terminal functions.
#include <iostream>
// Functions for grabbing pngs through paths.
#include <QDesktopServices>
#include <QUrl>
// Contains functions for the timer.
#include <QTimer>
// Function to grab current time.
#include <QDateTime>
// Includes the QtWidgets.
#include <QtWidgets>

// Namespace
using namespace std;


// Main
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Creates the MainWindow ui.
    ui->setupUi(this);

    // Gives the window a title.
    this->setWindowTitle("ExOEx - Build: Main Sequence");

    // Gives a label a pixel map (banner/photo).
    QPixmap banner("resorces/banner.jpg");
    ui->label_banner->setPixmap(banner);

    // Initialises the MW's clock.
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
    timer->start();
}

// This function removes the MainWindow ui when it's closed.
MainWindow::~MainWindow()
{
    delete ui;
}


// Completed Functions
// Function for running Arc.exec when run button is clicked.
void MainWindow::on_pushButton_run_clicked()
{
    // Gets the location of ArcGUI (should be in folder above Arc.exec.
    cout << ".exec at: "<< getenv("PWD") << "kk?" << endl;
}

// Displays the current time in hh:mm:ss format.
void MainWindow::showTime(){

    // Grabs the current time in the form of a QTime.
    QTime time = QTime::currentTime();

    // Converts QTime to a QString for printing.
    QString time_text = time.toString("hh : mm : ss");

    // 'Blinks' the colons.
    if (time.msec() > 500){
        time_text[3] = ' ';
        time_text[8] = ' ';
    }

    // Changes the QString for label_clock to that of the time QString.
    ui->label_clock->setText(time_text);

    return;
}
