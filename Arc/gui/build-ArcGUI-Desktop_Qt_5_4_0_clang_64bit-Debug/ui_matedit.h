/********************************************************************************
** Form generated from reading UI file 'matedit.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATEDIT_H
#define UI_MATEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_matEdit
{
public:
    QPushButton *pushButton_update;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit_name;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBox_kappa;
    QLabel *label_8;
    QDoubleSpinBox *doubleSpinBox_albedo;
    QLabel *label_9;
    QComboBox *comboBox_scatter_type;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_cancel;
    QPushButton *pushButton_done;

    void setupUi(QDialog *matEdit)
    {
        if (matEdit->objectName().isEmpty())
            matEdit->setObjectName(QStringLiteral("matEdit"));
        matEdit->resize(237, 192);
        pushButton_update = new QPushButton(matEdit);
        pushButton_update->setObjectName(QStringLiteral("pushButton_update"));
        pushButton_update->setGeometry(QRect(100, 0, 115, 32));
        widget = new QWidget(matEdit);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(12, 30, 212, 124));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit_name = new QLineEdit(widget);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        font.setStrikeOut(false);
        lineEdit_name->setFont(font);
        lineEdit_name->setReadOnly(false);

        gridLayout->addWidget(lineEdit_name, 0, 1, 1, 1);

        label_7 = new QLabel(widget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 1, 0, 1, 1);

        doubleSpinBox_kappa = new QDoubleSpinBox(widget);
        doubleSpinBox_kappa->setObjectName(QStringLiteral("doubleSpinBox_kappa"));
        doubleSpinBox_kappa->setAccelerated(true);
        doubleSpinBox_kappa->setDecimals(4);
        doubleSpinBox_kappa->setMaximum(1e+06);
        doubleSpinBox_kappa->setSingleStep(0.01);
        doubleSpinBox_kappa->setValue(1);

        gridLayout->addWidget(doubleSpinBox_kappa, 1, 1, 1, 1);

        label_8 = new QLabel(widget);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 2, 0, 1, 1);

        doubleSpinBox_albedo = new QDoubleSpinBox(widget);
        doubleSpinBox_albedo->setObjectName(QStringLiteral("doubleSpinBox_albedo"));
        doubleSpinBox_albedo->setAccelerated(true);
        doubleSpinBox_albedo->setMaximum(1);
        doubleSpinBox_albedo->setSingleStep(0.01);
        doubleSpinBox_albedo->setValue(1);

        gridLayout->addWidget(doubleSpinBox_albedo, 2, 1, 1, 1);

        label_9 = new QLabel(widget);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 3, 0, 1, 1);

        comboBox_scatter_type = new QComboBox(widget);
        comboBox_scatter_type->setObjectName(QStringLiteral("comboBox_scatter_type"));

        gridLayout->addWidget(comboBox_scatter_type, 3, 1, 1, 1);

        widget1 = new QWidget(matEdit);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(80, 160, 158, 32));
        horizontalLayout = new QHBoxLayout(widget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_cancel = new QPushButton(widget1);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));

        horizontalLayout->addWidget(pushButton_cancel);

        pushButton_done = new QPushButton(widget1);
        pushButton_done->setObjectName(QStringLiteral("pushButton_done"));

        horizontalLayout->addWidget(pushButton_done);

        QWidget::setTabOrder(pushButton_update, lineEdit_name);
        QWidget::setTabOrder(lineEdit_name, doubleSpinBox_kappa);
        QWidget::setTabOrder(doubleSpinBox_kappa, doubleSpinBox_albedo);
        QWidget::setTabOrder(doubleSpinBox_albedo, comboBox_scatter_type);
        QWidget::setTabOrder(comboBox_scatter_type, pushButton_cancel);
        QWidget::setTabOrder(pushButton_cancel, pushButton_done);

        retranslateUi(matEdit);
        QObject::connect(pushButton_cancel, SIGNAL(clicked()), matEdit, SLOT(close()));
        QObject::connect(pushButton_done, SIGNAL(clicked()), matEdit, SLOT(close()));

        QMetaObject::connectSlotsByName(matEdit);
    } // setupUi

    void retranslateUi(QDialog *matEdit)
    {
        matEdit->setWindowTitle(QApplication::translate("matEdit", "Dialog", 0));
        pushButton_update->setText(QApplication::translate("matEdit", "Update", 0));
        label->setText(QApplication::translate("matEdit", "Name", 0));
        label_7->setText(QApplication::translate("matEdit", "Kappa", 0));
        label_8->setText(QApplication::translate("matEdit", "Albedo", 0));
        label_9->setText(QApplication::translate("matEdit", "Scatter type", 0));
        pushButton_cancel->setText(QApplication::translate("matEdit", "Cancel", 0));
        pushButton_done->setText(QApplication::translate("matEdit", "Done", 0));
    } // retranslateUi

};

namespace Ui {
    class matEdit: public Ui_matEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATEDIT_H
