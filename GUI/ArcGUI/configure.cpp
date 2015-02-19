#include "configure.h"
#include "ui_configure.h"

#include "matedit.h"

#include <iostream>
#include <fstream>

using namespace std;

Configure::Configure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Configure)
{
    ui->setupUi(this);

    populateLists();
}

Configure::~Configure()
{
    delete ui;
}


void Configure::on_pushButton_edit_material_clicked(){

    MatEdit matedit;

    matedit.setModal(true);
    matedit.exec();
}

void Configure::on_pushButton_done_clicked()
{
    ofstream config("Configure/config.txt");
    ofstream structure("Configure/struct.txt");
    ofstream matList("Configure/matList.txt");

    config << "nPhot " << ui->spinBox_nPhot->value() << endl;
    config << "nLayers " << ui->spinBox_nLayers->value() << endl;
    config << "wavelength " << ui->spinBox_wavelength->value() << endl;
    config << "END" << endl;

    structure << "END" << endl;

    for (int i=0; i<ui->listWidget_add_material->count(); i++){
        QString qName = ui->listWidget_add_material->item(i)->text();
        string name = qName.toUtf8().constData();
        matList << name << endl;
    }

    return;
}

void Configure::populateLists(){

    ifstream matList("Configure/matList.txt");

    if (!matList)
        cerr << "Could not open matlist.txt" << endl;

    while (matList){
        string name;
        matList >> name;
        if (name.length() > 1){
            QString qName = QString::fromStdString(name);
            ui->listWidget_add_material->addItem(qName);
            ui->listWidget_known_materials->addItem(qName);
        }
    }

    return;
}

void Configure::on_pushButton_add_clicked()
{
    QString mat = ui->listWidget_add_material->currentItem()->text();
    double radius = ui->doubleSpinBox_radius->value();

    QString qRadius = QString::number(radius);

    ui->listWidget_build->addItem(mat);
    ui->listWidget_radius->addItem(qRadius);
}

void Configure::on_pushButton_remove_clicked()
{
    index = ui->listWidget_build->row(selectedItems());
    cout << index << endl;
}
