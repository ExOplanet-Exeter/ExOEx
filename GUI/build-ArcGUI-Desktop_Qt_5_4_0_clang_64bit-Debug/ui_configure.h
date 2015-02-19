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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Configure
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *label_numbe_of_layers;
    QLabel *label_number_of_photons;
    QLabel *label_photon_wavelengthnm;
    QSpinBox *spinBox_nPhot;
    QSpinBox *spinBox_nLayers;
    QSpinBox *spinBox_wavelength;
    QWidget *tab_2;
    QGridLayout *gridLayout_4;
    QLabel *label_add_material;
    QVBoxLayout *verticalLayout;
    QLabel *label_radius;
    QDoubleSpinBox *doubleSpinBox_radius;
    QPushButton *pushButton_add;
    QLabel *label_6;
    QPushButton *pushButton_remove;
    QLabel *label_build;
    QLabel *label_radius_2;
    QListWidget *listWidget_add_material;
    QListWidget *listWidget_build;
    QListWidget *listWidget_radius;
    QWidget *tab_3;
    QGridLayout *gridLayout_5;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_known_materials;
    QListWidget *listWidget_known_materials;
    QPushButton *pushButton_edit_material;
    QFormLayout *formLayout;
    QLabel *label_name;
    QLineEdit *lineEdit_name;
    QLabel *label_kappa;
    QDoubleSpinBox *doubleSpinBox_kappa;
    QLabel *label_albedo;
    QDoubleSpinBox *doubleSpinBox_albedo;
    QLabel *label_scatter_type;
    QComboBox *comboBox_scatter_type;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_add_new_material;
    QSpacerItem *horizontalSpacer_3;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_cancel;
    QPushButton *pushButton_done;

    void setupUi(QDialog *Configure)
    {
        if (Configure->objectName().isEmpty())
            Configure->setObjectName(QStringLiteral("Configure"));
        Configure->resize(479, 310);
        gridLayout = new QGridLayout(Configure);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(Configure);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMovable(true);
        tabWidget->setTabBarAutoHide(false);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_numbe_of_layers = new QLabel(tab);
        label_numbe_of_layers->setObjectName(QStringLiteral("label_numbe_of_layers"));
        label_numbe_of_layers->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_numbe_of_layers, 1, 0, 1, 1);

        label_number_of_photons = new QLabel(tab);
        label_number_of_photons->setObjectName(QStringLiteral("label_number_of_photons"));
        label_number_of_photons->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_number_of_photons, 0, 0, 1, 1);

        label_photon_wavelengthnm = new QLabel(tab);
        label_photon_wavelengthnm->setObjectName(QStringLiteral("label_photon_wavelengthnm"));
        label_photon_wavelengthnm->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_photon_wavelengthnm, 2, 0, 1, 1);

        spinBox_nPhot = new QSpinBox(tab);
        spinBox_nPhot->setObjectName(QStringLiteral("spinBox_nPhot"));
        spinBox_nPhot->setAccelerated(true);
        spinBox_nPhot->setMaximum(1000000000);
        spinBox_nPhot->setValue(100000);

        gridLayout_2->addWidget(spinBox_nPhot, 0, 1, 1, 1);

        spinBox_nLayers = new QSpinBox(tab);
        spinBox_nLayers->setObjectName(QStringLiteral("spinBox_nLayers"));
        spinBox_nLayers->setAccelerated(true);
        spinBox_nLayers->setMinimum(1);

        gridLayout_2->addWidget(spinBox_nLayers, 1, 1, 1, 1);

        spinBox_wavelength = new QSpinBox(tab);
        spinBox_wavelength->setObjectName(QStringLiteral("spinBox_wavelength"));
        spinBox_wavelength->setAccelerated(true);
        spinBox_wavelength->setMinimum(1);
        spinBox_wavelength->setMaximum(20000);
        spinBox_wavelength->setValue(500);

        gridLayout_2->addWidget(spinBox_wavelength, 2, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_4 = new QGridLayout(tab_2);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label_add_material = new QLabel(tab_2);
        label_add_material->setObjectName(QStringLiteral("label_add_material"));
        label_add_material->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_add_material, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_radius = new QLabel(tab_2);
        label_radius->setObjectName(QStringLiteral("label_radius"));
        label_radius->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_radius);

        doubleSpinBox_radius = new QDoubleSpinBox(tab_2);
        doubleSpinBox_radius->setObjectName(QStringLiteral("doubleSpinBox_radius"));
        doubleSpinBox_radius->setAccelerated(true);
        doubleSpinBox_radius->setMaximum(1);
        doubleSpinBox_radius->setSingleStep(0.01);
        doubleSpinBox_radius->setValue(1);

        verticalLayout->addWidget(doubleSpinBox_radius);

        pushButton_add = new QPushButton(tab_2);
        pushButton_add->setObjectName(QStringLiteral("pushButton_add"));

        verticalLayout->addWidget(pushButton_add);

        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout->addWidget(label_6);

        pushButton_remove = new QPushButton(tab_2);
        pushButton_remove->setObjectName(QStringLiteral("pushButton_remove"));

        verticalLayout->addWidget(pushButton_remove);


        gridLayout_4->addLayout(verticalLayout, 1, 1, 1, 1);

        label_build = new QLabel(tab_2);
        label_build->setObjectName(QStringLiteral("label_build"));
        label_build->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_build, 0, 2, 1, 1);

        label_radius_2 = new QLabel(tab_2);
        label_radius_2->setObjectName(QStringLiteral("label_radius_2"));
        label_radius_2->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_radius_2, 0, 3, 1, 1);

        listWidget_add_material = new QListWidget(tab_2);
        listWidget_add_material->setObjectName(QStringLiteral("listWidget_add_material"));

        gridLayout_4->addWidget(listWidget_add_material, 1, 0, 1, 1);

        listWidget_build = new QListWidget(tab_2);
        listWidget_build->setObjectName(QStringLiteral("listWidget_build"));

        gridLayout_4->addWidget(listWidget_build, 1, 2, 1, 1);

        listWidget_radius = new QListWidget(tab_2);
        listWidget_radius->setObjectName(QStringLiteral("listWidget_radius"));

        gridLayout_4->addWidget(listWidget_radius, 1, 3, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayout_5 = new QGridLayout(tab_3);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_known_materials = new QLabel(tab_3);
        label_known_materials->setObjectName(QStringLiteral("label_known_materials"));
        label_known_materials->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_known_materials);

        listWidget_known_materials = new QListWidget(tab_3);
        listWidget_known_materials->setObjectName(QStringLiteral("listWidget_known_materials"));

        verticalLayout_2->addWidget(listWidget_known_materials);

        pushButton_edit_material = new QPushButton(tab_3);
        pushButton_edit_material->setObjectName(QStringLiteral("pushButton_edit_material"));

        verticalLayout_2->addWidget(pushButton_edit_material);


        gridLayout_5->addLayout(verticalLayout_2, 0, 0, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
        label_name = new QLabel(tab_3);
        label_name->setObjectName(QStringLiteral("label_name"));
        label_name->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, label_name);

        lineEdit_name = new QLineEdit(tab_3);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_name);

        label_kappa = new QLabel(tab_3);
        label_kappa->setObjectName(QStringLiteral("label_kappa"));
        label_kappa->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_kappa);

        doubleSpinBox_kappa = new QDoubleSpinBox(tab_3);
        doubleSpinBox_kappa->setObjectName(QStringLiteral("doubleSpinBox_kappa"));
        doubleSpinBox_kappa->setAccelerated(true);
        doubleSpinBox_kappa->setDecimals(4);
        doubleSpinBox_kappa->setMinimum(0);
        doubleSpinBox_kappa->setMaximum(1000);
        doubleSpinBox_kappa->setSingleStep(0.1);
        doubleSpinBox_kappa->setValue(1);

        formLayout->setWidget(1, QFormLayout::FieldRole, doubleSpinBox_kappa);

        label_albedo = new QLabel(tab_3);
        label_albedo->setObjectName(QStringLiteral("label_albedo"));
        label_albedo->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(2, QFormLayout::LabelRole, label_albedo);

        doubleSpinBox_albedo = new QDoubleSpinBox(tab_3);
        doubleSpinBox_albedo->setObjectName(QStringLiteral("doubleSpinBox_albedo"));
        doubleSpinBox_albedo->setAccelerated(true);
        doubleSpinBox_albedo->setDecimals(2);
        doubleSpinBox_albedo->setMinimum(0);
        doubleSpinBox_albedo->setMaximum(1);
        doubleSpinBox_albedo->setSingleStep(0.01);
        doubleSpinBox_albedo->setValue(1);

        formLayout->setWidget(2, QFormLayout::FieldRole, doubleSpinBox_albedo);

        label_scatter_type = new QLabel(tab_3);
        label_scatter_type->setObjectName(QStringLiteral("label_scatter_type"));
        label_scatter_type->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(3, QFormLayout::LabelRole, label_scatter_type);

        comboBox_scatter_type = new QComboBox(tab_3);
        comboBox_scatter_type->setObjectName(QStringLiteral("comboBox_scatter_type"));

        formLayout->setWidget(3, QFormLayout::FieldRole, comboBox_scatter_type);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButton_add_new_material = new QPushButton(tab_3);
        pushButton_add_new_material->setObjectName(QStringLiteral("pushButton_add_new_material"));

        horizontalLayout_2->addWidget(pushButton_add_new_material);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        formLayout->setLayout(4, QFormLayout::SpanningRole, horizontalLayout_2);


        gridLayout_5->addLayout(formLayout, 0, 2, 1, 1);

        line = new QFrame(tab_3);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_5->addWidget(line, 0, 1, 1, 1);

        tabWidget->addTab(tab_3, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_cancel = new QPushButton(Configure);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));

        horizontalLayout->addWidget(pushButton_cancel);

        pushButton_done = new QPushButton(Configure);
        pushButton_done->setObjectName(QStringLiteral("pushButton_done"));

        horizontalLayout->addWidget(pushButton_done);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);


        retranslateUi(Configure);
        QObject::connect(pushButton_cancel, SIGNAL(clicked()), Configure, SLOT(close()));
        QObject::connect(pushButton_done, SIGNAL(clicked()), Configure, SLOT(close()));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Configure);
    } // setupUi

    void retranslateUi(QDialog *Configure)
    {
        Configure->setWindowTitle(QApplication::translate("Configure", "Dialog", 0));
        label_numbe_of_layers->setText(QApplication::translate("Configure", "Number of Layers", 0));
        label_number_of_photons->setText(QApplication::translate("Configure", "Number of Photons", 0));
        label_photon_wavelengthnm->setText(QApplication::translate("Configure", "Photon Wavelength (nm)", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Configure", " General ", 0));
        label_add_material->setText(QApplication::translate("Configure", "Add Material", 0));
        label_radius->setText(QApplication::translate("Configure", "Radius", 0));
        pushButton_add->setText(QApplication::translate("Configure", "Add", 0));
        label_6->setText(QString());
        pushButton_remove->setText(QApplication::translate("Configure", "Remove", 0));
        label_build->setText(QApplication::translate("Configure", "Build", 0));
        label_radius_2->setText(QApplication::translate("Configure", "Radius", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Configure", "Structure", 0));
        label_known_materials->setText(QApplication::translate("Configure", "Known Materials", 0));
        pushButton_edit_material->setText(QApplication::translate("Configure", "Edit", 0));
        label_name->setText(QApplication::translate("Configure", "Name", 0));
        label_kappa->setText(QApplication::translate("Configure", "Kappa", 0));
        label_albedo->setText(QApplication::translate("Configure", "Albedo", 0));
        label_scatter_type->setText(QApplication::translate("Configure", "Scatter Type", 0));
        pushButton_add_new_material->setText(QApplication::translate("Configure", " Add ", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("Configure", "Materials", 0));
        pushButton_cancel->setText(QApplication::translate("Configure", "Cancel", 0));
        pushButton_done->setText(QApplication::translate("Configure", "Done", 0));
    } // retranslateUi

};

namespace Ui {
    class Configure: public Ui_Configure {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGURE_H
