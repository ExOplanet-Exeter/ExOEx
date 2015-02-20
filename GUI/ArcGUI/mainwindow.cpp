#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "credits.h"

// Header file for the config window.
#include <configure.h>
// File functions.
#include <fstream>
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


// Function Prototypes
string getExOExPathString();


// Main
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Creates the MainWindow ui.
    ui->setupUi(this);

    // Gives the window a title.
    this->setWindowTitle("ExOEx - Build: Main Sequence");

    system("ls");

    // Gives a label a pixel map (banner/photo).
    QPixmap banner("Resorces/banner.png");
    ui->label_banner->setPixmap(banner);
    ui->label_banner->setScaledContents(true);

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
string MainWindow::getExOExPathString(){

    // Change working directory to ~/ExOEx/
    ifstream file("Resorces/path.txt");

    if (!file){
        QMessageBox::information(this,tr("ERROR!"),tr("ERROR!\n\npath.txt not found.\nYou likely need to run ./config."));
    }

    string path;
    file >> path;

    return path;
}

// Function for running Arc.exec when run button is clicked.
void MainWindow::on_pushButton_run_clicked(){

    QString arcPath = "Arc/arc";

    QProcess::execute(arcPath, QStringList());

    return;
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

// Opens the configure window.
void MainWindow::on_pushButton_configure_clicked()
{
    Configure configure;
    configure.setModal(true);
    configure.exec();
}

// Opens the credits window.
void MainWindow::on_pushButton_credits_clicked()
{
    Credits credits;
    credits.setModal(true);
    credits.exec();
}
