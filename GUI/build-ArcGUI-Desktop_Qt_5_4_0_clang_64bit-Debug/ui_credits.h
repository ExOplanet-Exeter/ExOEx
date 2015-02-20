/********************************************************************************
** Form generated from reading UI file 'credits.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREDITS_H
#define UI_CREDITS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_Credits
{
public:
    QGridLayout *gridLayout;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_2;
    QLabel *label_6;
    QLabel *label_3;
    QLabel *label_7;
    QLabel *label_4;
    QLabel *label_8;
    QLabel *label_5;
    QLabel *label_9;
    QLabel *label;

    void setupUi(QDialog *Credits)
    {
        if (Credits->objectName().isEmpty())
            Credits->setObjectName(QStringLiteral("Credits"));
        Credits->resize(255, 206);
        gridLayout = new QGridLayout(Credits);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_10 = new QLabel(Credits);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 1, 1, 1, 1);

        label_11 = new QLabel(Credits);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 1, 2, 1, 1);

        label_2 = new QLabel(Credits);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label_6 = new QLabel(Credits);
        label_6->setObjectName(QStringLiteral("label_6"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_6->setFont(font);
        label_6->setTextFormat(Qt::PlainText);

        gridLayout->addWidget(label_6, 2, 2, 1, 1);

        label_3 = new QLabel(Credits);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        label_7 = new QLabel(Credits);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font);
        label_7->setTextFormat(Qt::PlainText);

        gridLayout->addWidget(label_7, 3, 2, 1, 1);

        label_4 = new QLabel(Credits);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        label_8 = new QLabel(Credits);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font);
        label_8->setTextFormat(Qt::PlainText);

        gridLayout->addWidget(label_8, 4, 2, 1, 1);

        label_5 = new QLabel(Credits);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_5, 5, 0, 1, 1);

        label_9 = new QLabel(Credits);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setFont(font);
        label_9->setTextFormat(Qt::PlainText);

        gridLayout->addWidget(label_9, 5, 2, 1, 1);

        label = new QLabel(Credits);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setPointSize(20);
        font1.setBold(true);
        font1.setUnderline(true);
        font1.setWeight(75);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 3);


        retranslateUi(Credits);

        QMetaObject::connectSlotsByName(Credits);
    } // setupUi

    void retranslateUi(QDialog *Credits)
    {
        Credits->setWindowTitle(QApplication::translate("Credits", "Dialog", 0));
        label_10->setText(QString());
        label_11->setText(QString());
        label_2->setText(QApplication::translate("Credits", "        Supervisor", 0));
        label_6->setText(QApplication::translate("Credits", "Proff. Tim Harries", 0));
        label_3->setText(QApplication::translate("Credits", "Team Member 1", 0));
        label_7->setText(QApplication::translate("Credits", "E. Bahl", 0));
        label_4->setText(QApplication::translate("Credits", "Team Member 2", 0));
        label_8->setText(QApplication::translate("Credits", "B. Nickson", 0));
        label_5->setText(QApplication::translate("Credits", "Team Member 3", 0));
        label_9->setText(QApplication::translate("Credits", "F. Wordingham", 0));
        label->setText(QApplication::translate("Credits", "Credits", 0));
    } // retranslateUi

};

namespace Ui {
    class Credits: public Ui_Credits {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREDITS_H
