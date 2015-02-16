/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label_picture;
    QFrame *line;
    QWidget *widget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_run;
    QPushButton *pushButton_configure;
    QPushButton *pushButton_exit;
    QLabel *label_clock;
    QMenuBar *menuBar;
    QMenu *menuArchius_Universe;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(312, 283);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_picture = new QLabel(centralWidget);
        label_picture->setObjectName(QStringLiteral("label_picture"));
        label_picture->setGeometry(QRect(30, 20, 250, 110));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(5, 140, 301, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 160, 271, 69));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_run = new QPushButton(widget);
        pushButton_run->setObjectName(QStringLiteral("pushButton_run"));

        gridLayout->addWidget(pushButton_run, 0, 0, 1, 1);

        pushButton_configure = new QPushButton(widget);
        pushButton_configure->setObjectName(QStringLiteral("pushButton_configure"));

        gridLayout->addWidget(pushButton_configure, 0, 1, 1, 1);

        pushButton_exit = new QPushButton(widget);
        pushButton_exit->setObjectName(QStringLiteral("pushButton_exit"));

        gridLayout->addWidget(pushButton_exit, 1, 1, 1, 1);

        label_clock = new QLabel(widget);
        label_clock->setObjectName(QStringLiteral("label_clock"));
        QFont font;
        font.setPointSize(17);
        font.setBold(false);
        font.setWeight(50);
        label_clock->setFont(font);
        label_clock->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_clock, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 312, 22));
        menuArchius_Universe = new QMenu(menuBar);
        menuArchius_Universe->setObjectName(QStringLiteral("menuArchius_Universe"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuArchius_Universe->menuAction());

        retranslateUi(MainWindow);
        QObject::connect(pushButton_exit, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label_picture->setText(QString());
        pushButton_run->setText(QApplication::translate("MainWindow", "Run ExOEx", 0));
        pushButton_configure->setText(QApplication::translate("MainWindow", "Configure", 0));
        pushButton_exit->setText(QApplication::translate("MainWindow", "Exit", 0));
        label_clock->setText(QApplication::translate("MainWindow", "Clock", 0));
        menuArchius_Universe->setTitle(QApplication::translate("MainWindow", "Archius Universe", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
