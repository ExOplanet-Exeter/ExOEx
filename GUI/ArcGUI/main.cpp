#include "mainwindow.h"
#include <QApplication>

// Functions for terminal printing.
#include <iostream>
// Functions for operating files.
#include <fstream>
// Contains needed change directory function.
#include <unistd.h>
// Function for creating messgae boxes.
#include <QMessageBox>
// Contains functions for grabbing directory paths.
#include <stdlib.h>
// Functions for manipulating strings.
#include <string>

// Namespace
using namespace std;


// Main
int main(int argc, char *argv[])
{   
    // // This section changes the CWD to that of /ExOEx/
    string p1 = argv[0];
    string p2 = getenv("PWD");
    int Ex1 = 0, Ex2 = 0;

    // Locate 'GUI' in the file path.
    Ex1 = p1.find("ExOEx") + 6;
    Ex2 = p2.find("ExOEx") + 6;

    // Remove anything past /ExOEx/
    // Then change directory to the path.
    if ((Ex1>0) && (Ex1>Ex2)){
        p1.erase (p1.begin()+Ex1,p1.end());
        cout << p1 << endl;
        chdir(p1.c_str());
    }
    if ((Ex2>0) && (Ex2>Ex1)){
        p2.erase (p2.begin()+Ex2,p2.end());
        cout << p2 << endl;
        chdir(p2.c_str());
    }

    // // Creates the MainWindow GUI.
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
