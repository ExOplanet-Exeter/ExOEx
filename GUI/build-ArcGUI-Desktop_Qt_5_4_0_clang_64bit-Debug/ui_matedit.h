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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_MatEdit
{
public:
    QGridLayout *gridLayout;
    QLabel *label_name;
    QLineEdit *lineEdit_name;
    QLabel *label_kappa;
    QDoubleSpinBox *doubleSpinBox_kappa;
    QLabel *label_albedo;
    QDoubleSpinBox *doubleSpinBox_albedo;
    QLabel *label_scatter_type;
    QComboBox *comboBox_scatter_type;
    QPushButton *pushButton_cancel;
    QPushButton *pushButton_done;

    void setupUi(QDialog *MatEdit)
    {
        if (MatEdit->objectName().isEmpty())
            MatEdit->setObjectName(QStringLiteral("MatEdit"));
        MatEdit->resize(213, 177);
        gridLayout = new QGridLayout(MatEdit);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_name = new QLabel(MatEdit);
        label_name->setObjectName(QStringLiteral("label_name"));
        label_name->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_name, 0, 0, 1, 1);

        lineEdit_name = new QLineEdit(MatEdit);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));
        lineEdit_name->setEnabled(false);
        lineEdit_name->setReadOnly(true);

        gridLayout->addWidget(lineEdit_name, 0, 1, 1, 1);

        label_kappa = new QLabel(MatEdit);
        label_kappa->setObjectName(QStringLiteral("label_kappa"));
        label_kappa->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_kappa, 1, 0, 1, 1);

        doubleSpinBox_kappa = new QDoubleSpinBox(MatEdit);
        doubleSpinBox_kappa->setObjectName(QStringLiteral("doubleSpinBox_kappa"));
        doubleSpinBox_kappa->setAccelerated(true);
        doubleSpinBox_kappa->setMaximum(1000);
        doubleSpinBox_kappa->setSingleStep(0.1);
        doubleSpinBox_kappa->setValue(1);

        gridLayout->addWidget(doubleSpinBox_kappa, 1, 1, 1, 1);

        label_albedo = new QLabel(MatEdit);
        label_albedo->setObjectName(QStringLiteral("label_albedo"));
        label_albedo->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_albedo, 2, 0, 1, 1);

        doubleSpinBox_albedo = new QDoubleSpinBox(MatEdit);
        doubleSpinBox_albedo->setObjectName(QStringLiteral("doubleSpinBox_albedo"));
        doubleSpinBox_albedo->setAccelerated(true);
        doubleSpinBox_albedo->setMaximum(1);
        doubleSpinBox_albedo->setSingleStep(0.01);
        doubleSpinBox_albedo->setValue(1);

        gridLayout->addWidget(doubleSpinBox_albedo, 2, 1, 1, 1);

        label_scatter_type = new QLabel(MatEdit);
        label_scatter_type->setObjectName(QStringLiteral("label_scatter_type"));
        label_scatter_type->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_scatter_type, 3, 0, 1, 1);

        comboBox_scatter_type = new QComboBox(MatEdit);
        comboBox_scatter_type->setObjectName(QStringLiteral("comboBox_scatter_type"));

        gridLayout->addWidget(comboBox_scatter_type, 3, 1, 1, 1);

        pushButton_cancel = new QPushButton(MatEdit);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));

        gridLayout->addWidget(pushButton_cancel, 4, 0, 1, 1);

        pushButton_done = new QPushButton(MatEdit);
        pushButton_done->setObjectName(QStringLiteral("pushButton_done"));

        gridLayout->addWidget(pushButton_done, 4, 1, 1, 1);


        retranslateUi(MatEdit);
        QObject::connect(pushButton_cancel, SIGNAL(clicked()), MatEdit, SLOT(close()));
        QObject::connect(pushButton_done, SIGNAL(clicked()), MatEdit, SLOT(close()));

        QMetaObject::connectSlotsByName(MatEdit);
    } // setupUi

    void retranslateUi(QDialog *MatEdit)
    {
        MatEdit->setWindowTitle(QApplication::translate("MatEdit", "Dialog", 0));
        label_name->setText(QApplication::translate("MatEdit", "Name", 0));
        label_kappa->setText(QApplication::translate("MatEdit", "Kappa", 0));
        label_albedo->setText(QApplication::translate("MatEdit", "Albedo", 0));
        label_scatter_type->setText(QApplication::translate("MatEdit", "Scatter Type", 0));
        pushButton_cancel->setText(QApplication::translate("MatEdit", "Cancel", 0));
        pushButton_done->setText(QApplication::translate("MatEdit", "Done", 0));
    } // retranslateUi

};

namespace Ui {
    class MatEdit: public Ui_MatEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATEDIT_H
