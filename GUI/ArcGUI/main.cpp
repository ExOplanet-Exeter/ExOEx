#include "mainwindow.h"
#include <QApplication>


// Namespace


// Function Prototypes


// Main
int main(int argc, char *argv[])
{   
    // Creates the MainWindow GUI.
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}


// Completed functions
