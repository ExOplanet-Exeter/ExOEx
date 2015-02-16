/********************************************************************************
** Form generated from reading UI file 'configure.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGURE_H
#define UI_CONFIGURE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Configure
{
public:
    QPushButton *pushButton_exit;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *pushButton_save_config;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *spinBox_nPhot;
    QLabel *label_2;
    QSpinBox *spinBox_nLayers;
    QLabel *label_3;
    QSpinBox *spinBox_wavelength;
    QWidget *tab_2;
    QPushButton *pushButton_add;
    QPushButton *pushButton_remove;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QListWidget *listWidget_mat_list;
    QPushButton *pushButton_invis;
    QLabel *label_12;
    QDoubleSpinBox *doubleSpinBox_radius;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QLabel *label_5;
    QListWidget *listWidget_build;
    QListWidget *listWidget_radius;
    QPushButton *pushButton_save_struct;
    QLabel *label_11;
    QWidget *tab_3;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_6;
    QListWidget *listWidget_known_mats;
    QPushButton *pushButton_edit_material;
    QFrame *line;
    QPushButton *pushButton_new_mat;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout_2;
    QLabel *label_10;
    QLineEdit *lineEdit_name;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBox_kappa;
    QLabel *label_8;
    QDoubleSpinBox *doubleSpinBox_albedo;
    QLabel *label_9;
    QComboBox *comboBox_scatter_type;
    QPushButton *pushButton_cancel;

    void setupUi(QDialog *Configure)
    {
        if (Configure->objectName().isEmpty())
            Configure->setObjectName(QStringLiteral("Configure"));
        Configure->resize(400, 300);
        pushButton_exit = new QPushButton(Configure);
        pushButton_exit->setObjectName(QStringLiteral("pushButton_exit"));
        pushButton_exit->setGeometry(QRect(281, 270, 110, 32));
        tabWidget = new QTabWidget(Configure);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 401, 271));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        pushButton_save_config = new QPushButton(tab);
        pushButton_save_config->setObjectName(QStringLiteral("pushButton_save_config"));
        pushButton_save_config->setGeometry(QRect(261, 205, 131, 32));
        QFont font;
        font.setKerning(true);
        pushButton_save_config->setFont(font);
        pushButton_save_config->setCheckable(false);
        pushButton_save_config->setAutoExclusive(false);
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(100, 40, 201, 131));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setPointSize(13);
        label->setFont(font1);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        spinBox_nPhot = new QSpinBox(layoutWidget);
        spinBox_nPhot->setObjectName(QStringLiteral("spinBox_nPhot"));
        spinBox_nPhot->setFont(font1);
        spinBox_nPhot->setAccelerated(true);
        spinBox_nPhot->setMaximum(1000000000);
        spinBox_nPhot->setValue(10000);

        gridLayout->addWidget(spinBox_nPhot, 0, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        spinBox_nLayers = new QSpinBox(layoutWidget);
        spinBox_nLayers->setObjectName(QStringLiteral("spinBox_nLayers"));
        spinBox_nLayers->setFont(font1);
        spinBox_nLayers->setAccelerated(true);
        spinBox_nLayers->setValue(1);

        gridLayout->addWidget(spinBox_nLayers, 1, 1, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font1);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        spinBox_wavelength = new QSpinBox(layoutWidget);
        spinBox_wavelength->setObjectName(QStringLiteral("spinBox_wavelength"));
        spinBox_wavelength->setFont(font1);
        spinBox_wavelength->setAccelerated(true);
        spinBox_wavelength->setMinimum(100);
        spinBox_wavelength->setMaximum(10000);
        spinBox_wavelength->setValue(500);

        gridLayout->addWidget(spinBox_wavelength, 2, 1, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        pushButton_add = new QPushButton(tab_2);
        pushButton_add->setObjectName(QStringLiteral("pushButton_add"));
        pushButton_add->setGeometry(QRect(136, 28, 81, 32));
        pushButton_remove = new QPushButton(tab_2);
        pushButton_remove->setObjectName(QStringLiteral("pushButton_remove"));
        pushButton_remove->setGeometry(QRect(136, 170, 81, 32));
        layoutWidget1 = new QWidget(tab_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(3, 6, 141, 231));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QStringLiteral("label_4"));
        QFont font2;
        font2.setPointSize(15);
        label_4->setFont(font2);
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_4);

        listWidget_mat_list = new QListWidget(layoutWidget1);
        listWidget_mat_list->setObjectName(QStringLiteral("listWidget_mat_list"));

        verticalLayout_3->addWidget(listWidget_mat_list);

        pushButton_invis = new QPushButton(layoutWidget1);
        pushButton_invis->setObjectName(QStringLiteral("pushButton_invis"));

        verticalLayout_3->addWidget(pushButton_invis);

        label_12 = new QLabel(tab_2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(147, 73, 59, 16));
        label_12->setAlignment(Qt::AlignCenter);
        doubleSpinBox_radius = new QDoubleSpinBox(tab_2);
        doubleSpinBox_radius->setObjectName(QStringLiteral("doubleSpinBox_radius"));
        doubleSpinBox_radius->setGeometry(QRect(144, 90, 66, 24));
        doubleSpinBox_radius->setAccelerated(true);
        doubleSpinBox_radius->setMaximum(1);
        doubleSpinBox_radius->setValue(1);
        widget = new QWidget(tab_2);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(210, 6, 181, 231));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font2);
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_5, 0, 0, 1, 1);

        listWidget_build = new QListWidget(widget);
        listWidget_build->setObjectName(QStringLiteral("listWidget_build"));

        gridLayout_3->addWidget(listWidget_build, 1, 0, 1, 1);

        listWidget_radius = new QListWidget(widget);
        listWidget_radius->setObjectName(QStringLiteral("listWidget_radius"));

        gridLayout_3->addWidget(listWidget_radius, 1, 1, 1, 1);

        pushButton_save_struct = new QPushButton(widget);
        pushButton_save_struct->setObjectName(QStringLiteral("pushButton_save_struct"));
        pushButton_save_struct->setCheckable(false);

        gridLayout_3->addWidget(pushButton_save_struct, 2, 0, 1, 2);

        label_11 = new QLabel(widget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setFont(font2);
        label_11->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_11, 0, 1, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        verticalLayoutWidget = new QWidget(tab_3);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(3, 6, 151, 231));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(verticalLayoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        QFont font3;
        font3.setPointSize(15);
        font3.setBold(false);
        font3.setWeight(50);
        label_6->setFont(font3);
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_6);

        listWidget_known_mats = new QListWidget(verticalLayoutWidget);
        listWidget_known_mats->setObjectName(QStringLiteral("listWidget_known_mats"));

        verticalLayout->addWidget(listWidget_known_mats);

        pushButton_edit_material = new QPushButton(verticalLayoutWidget);
        pushButton_edit_material->setObjectName(QStringLiteral("pushButton_edit_material"));

        verticalLayout->addWidget(pushButton_edit_material);

        line = new QFrame(tab_3);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(150, -10, 20, 251));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        pushButton_new_mat = new QPushButton(tab_3);
        pushButton_new_mat->setObjectName(QStringLiteral("pushButton_new_mat"));
        pushButton_new_mat->setGeometry(QRect(220, 180, 97, 32));
        layoutWidget2 = new QWidget(tab_3);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(173, 50, 212, 124));
        gridLayout_2 = new QGridLayout(layoutWidget2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(layoutWidget2);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_2->addWidget(label_10, 0, 0, 1, 1);

        lineEdit_name = new QLineEdit(layoutWidget2);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));
        lineEdit_name->setInputMethodHints(Qt::ImhLowercaseOnly);
        lineEdit_name->setMaxLength(16);

        gridLayout_2->addWidget(lineEdit_name, 0, 1, 1, 1);

        label_7 = new QLabel(layoutWidget2);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 1, 0, 1, 1);

        doubleSpinBox_kappa = new QDoubleSpinBox(layoutWidget2);
        doubleSpinBox_kappa->setObjectName(QStringLiteral("doubleSpinBox_kappa"));
        doubleSpinBox_kappa->setAccelerated(true);
        doubleSpinBox_kappa->setDecimals(4);
        doubleSpinBox_kappa->setMaximum(1e+06);
        doubleSpinBox_kappa->setSingleStep(0.01);
        doubleSpinBox_kappa->setValue(1);

        gridLayout_2->addWidget(doubleSpinBox_kappa, 1, 1, 1, 1);

        label_8 = new QLabel(layoutWidget2);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_2->addWidget(label_8, 2, 0, 1, 1);

        doubleSpinBox_albedo = new QDoubleSpinBox(layoutWidget2);
        doubleSpinBox_albedo->setObjectName(QStringLiteral("doubleSpinBox_albedo"));
        doubleSpinBox_albedo->setAccelerated(true);
        doubleSpinBox_albedo->setMaximum(1);
        doubleSpinBox_albedo->setSingleStep(0.01);
        doubleSpinBox_albedo->setValue(1);

        gridLayout_2->addWidget(doubleSpinBox_albedo, 2, 1, 1, 1);

        label_9 = new QLabel(layoutWidget2);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_2->addWidget(label_9, 3, 0, 1, 1);

        comboBox_scatter_type = new QComboBox(layoutWidget2);
        comboBox_scatter_type->setObjectName(QStringLiteral("comboBox_scatter_type"));

        gridLayout_2->addWidget(comboBox_scatter_type, 3, 1, 1, 1);

        tabWidget->addTab(tab_3, QString());
        pushButton_cancel = new QPushButton(Configure);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(171, 270, 110, 32));
        QWidget::setTabOrder(spinBox_nPhot, spinBox_nLayers);
        QWidget::setTabOrder(spinBox_nLayers, spinBox_wavelength);
        QWidget::setTabOrder(spinBox_wavelength, pushButton_save_config);
        QWidget::setTabOrder(pushButton_save_config, listWidget_mat_list);
        QWidget::setTabOrder(listWidget_mat_list, pushButton_add);
        QWidget::setTabOrder(pushButton_add, pushButton_remove);
        QWidget::setTabOrder(pushButton_remove, listWidget_build);
        QWidget::setTabOrder(listWidget_build, pushButton_save_struct);
        QWidget::setTabOrder(pushButton_save_struct, listWidget_known_mats);
        QWidget::setTabOrder(listWidget_known_mats, pushButton_edit_material);
        QWidget::setTabOrder(pushButton_edit_material, lineEdit_name);
        QWidget::setTabOrder(lineEdit_name, doubleSpinBox_kappa);
        QWidget::setTabOrder(doubleSpinBox_kappa, doubleSpinBox_albedo);
        QWidget::setTabOrder(doubleSpinBox_albedo, comboBox_scatter_type);
        QWidget::setTabOrder(comboBox_scatter_type, pushButton_new_mat);
        QWidget::setTabOrder(pushButton_new_mat, pushButton_exit);
        QWidget::setTabOrder(pushButton_exit, tabWidget);
        QWidget::setTabOrder(tabWidget, pushButton_invis);

        retranslateUi(Configure);
        QObject::connect(pushButton_exit, SIGNAL(clicked()), Configure, SLOT(close()));
        QObject::connect(pushButton_add, SIGNAL(pressed()), pushButton_save_struct, SLOT(setFocus()));
        QObject::connect(pushButton_cancel, SIGNAL(clicked()), Configure, SLOT(close()));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Configure);
    } // setupUi

    void retranslateUi(QDialog *Configure)
    {
        Configure->setWindowTitle(QApplication::translate("Configure", "Dialog", 0));
        pushButton_exit->setText(QApplication::translate("Configure", "Done", 0));
        pushButton_save_config->setText(QApplication::translate("Configure", "Save", 0));
        label->setText(QApplication::translate("Configure", "nPhotons", 0));
        label_2->setText(QApplication::translate("Configure", "nLayers", 0));
        label_3->setText(QApplication::translate("Configure", "Wavelength", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Configure", "config", 0));
        pushButton_add->setText(QApplication::translate("Configure", "Add", 0));
        pushButton_remove->setText(QApplication::translate("Configure", "Remove", 0));
        label_4->setText(QApplication::translate("Configure", "Avalible Materials", 0));
        pushButton_invis->setText(QApplication::translate("Configure", "PushButton", 0));
        label_12->setText(QApplication::translate("Configure", "Radius", 0));
        label_5->setText(QApplication::translate("Configure", "Build", 0));
        pushButton_save_struct->setText(QApplication::translate("Configure", "Save", 0));
        label_11->setText(QApplication::translate("Configure", "Radius", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Configure", "structure", 0));
        label_6->setText(QApplication::translate("Configure", "Known Materials", 0));
        pushButton_edit_material->setText(QApplication::translate("Configure", "Edit", 0));
        pushButton_new_mat->setText(QApplication::translate("Configure", "Add new", 0));
        label_10->setText(QApplication::translate("Configure", "Name", 0));
        label_7->setText(QApplication::translate("Configure", "Kappa", 0));
        label_8->setText(QApplication::translate("Configure", "Albedo", 0));
        label_9->setText(QApplication::translate("Configure", "Scatter type", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("Configure", "materials", 0));
        pushButton_cancel->setText(QApplication::translate("Configure", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class Configure: public Ui_Configure {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGURE_H
