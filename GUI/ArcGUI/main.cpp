#include "mainwindow.h"
#include <QApplication>

// Functions for operating files.
#include <fstream>
// Contains needed change directory function.
#include <unistd.h>
// Function for creating messgae boxes.
#include <QMessageBox>


// Namespace
using namespace std;


// Main
int main(int argc, char *argv[])
{   
    // Creates the MainWindow GUI.
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
