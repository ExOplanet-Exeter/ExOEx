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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
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
    QWidget *widget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_about;
    QPushButton *pushButton_run;
    QPushButton *pushButton_exit;
    QLabel *label_clock;
    QPushButton *pushButton_configure;
    QPushButton *pushButton_credits;
    QLabel *label_banner;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(8, 10, 381, 231));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_about = new QPushButton(widget);
        pushButton_about->setObjectName(QStringLiteral("pushButton_about"));

        gridLayout->addWidget(pushButton_about, 1, 0, 1, 1);

        pushButton_run = new QPushButton(widget);
        pushButton_run->setObjectName(QStringLiteral("pushButton_run"));

        gridLayout->addWidget(pushButton_run, 1, 1, 1, 1);

        pushButton_exit = new QPushButton(widget);
        pushButton_exit->setObjectName(QStringLiteral("pushButton_exit"));

        gridLayout->addWidget(pushButton_exit, 3, 2, 1, 1);

        label_clock = new QLabel(widget);
        label_clock->setObjectName(QStringLiteral("label_clock"));
        QFont font;
        font.setPointSize(17);
        label_clock->setFont(font);
        label_clock->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_clock, 3, 1, 1, 1);

        pushButton_configure = new QPushButton(widget);
        pushButton_configure->setObjectName(QStringLiteral("pushButton_configure"));

        gridLayout->addWidget(pushButton_configure, 1, 2, 1, 1);

        pushButton_credits = new QPushButton(widget);
        pushButton_credits->setObjectName(QStringLiteral("pushButton_credits"));

        gridLayout->addWidget(pushButton_credits, 3, 0, 1, 1);

        label_banner = new QLabel(widget);
        label_banner->setObjectName(QStringLiteral("label_banner"));

        gridLayout->addWidget(label_banner, 0, 0, 1, 3);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(pushButton_exit, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        pushButton_about->setText(QApplication::translate("MainWindow", "About", 0));
        pushButton_run->setText(QApplication::translate("MainWindow", "Run ExOEx", 0));
        pushButton_exit->setText(QApplication::translate("MainWindow", "Exit", 0));
        label_clock->setText(QApplication::translate("MainWindow", "00 : 00 : 00", 0));
        pushButton_configure->setText(QApplication::translate("MainWindow", "Configure", 0));
        pushButton_credits->setText(QApplication::translate("MainWindow", "Credits", 0));
        label_banner->setText(QApplication::translate("MainWindow", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
