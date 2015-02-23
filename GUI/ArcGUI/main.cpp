#include "mainwindow.h"
#include <QApplication>

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
// Functions to change window theme
#include <QStyleFactory>


// Namespace
using namespace std;


// Function Prototypes
void setWindowTheme();


// Main
int main(int argc, char *argv[])
{   
    // This section changes the CWD to that of /ExOEx/
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
        chdir(p1.c_str());
    }
    if ((Ex2>0) && (Ex2>Ex1)){
        p2.erase (p2.begin()+Ex2,p2.end());
        chdir(p2.c_str());
    }


    // Change window theme
    setWindowTheme();


    // Creates the MainWindow GUI.
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}


// Completed Functions
void setWindowTheme(){

    qApp->setStyle(QStyleFactory::create("Fusion"));

    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    qApp->setPalette(darkPalette);

    qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");

    return;
}
