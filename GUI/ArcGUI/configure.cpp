#include "configure.h"
#include "ui_configure.h"

#include "matedit.h"

#include <iostream>
#include <fstream>
#include <QMessageBox>

using namespace std;

Configure::Configure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Configure)
{
    ui->setupUi(this);

    populateLists();
    setupMatTable();
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

void Configure::setupMatTable(){

    int nLayers = ui->spinBox_nLayers->value();

    // Set number of rows/columns.
    ui->tableWidget_build->setColumnCount(2);
    ui->tableWidget_build->setRowCount(nLayers);

    // Set header text.
    ui->tableWidget_build->setHorizontalHeaderLabels(QString("   Material    ;    Radii   ").split(";"));

    // Set table size constraints.
    ui->tableWidget_build->resizeColumnsToContents();
    ui->tableWidget_build->resizeRowsToContents();

    // Add items for table cells.
    for (int i=0; i<nLayers; i++){
        ui->tableWidget_build->setItem(i,0,new QTableWidgetItem("-"));
        ui->tableWidget_build->setItem(i,1,new QTableWidgetItem("-"));
    }

    return;
}

void Configure::on_pushButton_add_clicked(){

    int nLayers = ui->spinBox_nLayers->value();

    bool freeSpace = false;
    for (int i=0; i<nLayers; i++){
        if (ui->tableWidget_build->item(i,0)->text() == "-"){
            freeSpace = true;
        }
    }

    if (freeSpace == false){
        QMessageBox::information(this,tr("Full"),tr("All layers occupied.\n\nPlease free a layer or increase number of layers in the 'General' tab."));
        return;
    }

    int row = -1;
    double radius = ui->doubleSpinBox_radius->value();
    QString qName = ui->listWidget_add_material->currentItem()->text();
    QString qRadius = QString::number(radius);

    for (int i=0; i<nLayers; i++){
        if (ui->tableWidget_build->item(i,0)->text() == "-"){
            ui->tableWidget_build->item(i,0)->setText(qName);
            ui->tableWidget_build->item(i,1)->setText(qRadius);
            row = i;
            break;
        }
    }

    for (int i=0; i<nLayers; i++){
        if ((QString(ui->tableWidget_build->item(i,1)->text()).toDouble() == radius) && (i != row)){
            ui->tableWidget_build->item(i,1)->setBackgroundColor(Qt::red);
            ui->tableWidget_build->item(row,1)->setBackgroundColor(Qt::red);
        }
    }

    return;
}

void Configure::on_pushButton_remove_clicked(){

    int row = ui->tableWidget_build->currentItem()->row();

    if (row != -1){
        ui->tableWidget_build->item(row,0)->setText("-");
        ui->tableWidget_build->item(row,1)->setText("-");
        ui->tableWidget_build->item(row,1)->setBackgroundColor(Qt::white);
    }

    return;
}

void Configure::on_pushButton_order_clicked()
{
    int nLayers = ui->spinBox_nLayers->value();
    int position[nLayers];
    double radius[nLayers];
    QStringList names;

    // Get all items in list. Position known through array index.
    for (int i=0; i<nLayers; i++){
        radius[i] = QString(ui->tableWidget_build->item(i,1)->text()).toDouble();
        names << ui->tableWidget_build->item(i,0)->text();
    }

    for (int i=0; i<nLayers; i++){
        for (int j=0; j<nLayers; j++){
            if ((ui->tableWidget_build->item(i,1)->row() != i) && (radius[i] == radius[j])){
                radius[i] = radius[i] - 0.001;
            }
        }
    }

    for (int i=0; i<nLayers; i++){
        position[i] = 0;
        for (int j=0; j<nLayers; j++){
            if (radius[i] > radius[j]){
                position[i]++;
            }
        }
        ui->tableWidget_build->item(position[i],0)->setText(names.at(i));
        ui->tableWidget_build->item(position[i],1)->setText(QString::number(radius[i]));
    }

    return;
}

void Configure::on_tableWidget_build_cellClicked(int row, int column)
{
    ui->pushButton_remove->setEnabled(true);
}
