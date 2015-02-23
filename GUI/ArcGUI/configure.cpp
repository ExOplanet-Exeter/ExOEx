#include "configure.h"
#include "ui_configure.h"

#include "matedit.h"

#include <fstream>
#include <QMessageBox>
#include <QStyleFactory>

using namespace std;

Configure::Configure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Configure)
{
    ui->setupUi(this);

    ui->tableWidget_build->setShowGrid(false);

    populateLists();
    setupMatTable();
    returnToPreviousValues();

}

Configure::~Configure()
{
    delete ui;
}


void Configure::returnToPreviousValues(){

    string word;

    // Returning General tab values.
    ifstream config("Configure/config.cfg");

    while (config){
        config >> word;
        if (word == "nPhot"){
            int nPhot;
            config >> nPhot;
            ui->spinBox_nPhot->setValue(nPhot);
        }
        else if (word == "nLayers"){
            int nLayers;
            config >> nLayers;
            ui->spinBox_nLayers->setValue(nLayers);
        }
        else if (word == "wavelength"){
            int wavelength;
            config >> wavelength;
            ui->spinBox_wavelength->setValue(wavelength);
        }
    }

    // Returning Structure setup.
    ifstream structure("Configure/struct.cfg");

    int i=0;
    while (structure){
        structure >> word;
        if (word == "END"){
            break;
        }
        else{
            double radius;
            string mat = word;
            QString qMat, qRadius;
            structure >> radius;
            qRadius = QString::number(radius);
            qMat = QString::fromStdString(mat);
            ui->tableWidget_build->item(i,0)->setText(qMat);
            ui->tableWidget_build->item(i,1)->setText(qRadius);
            i++;
        }

    }

    return;
}

void Configure::on_pushButton_edit_material_clicked(){

    MatEdit matedit;

    QString qMatName = ui->listWidget_known_materials->currentItem()->text();
    matedit.setName(qMatName);

    matedit.setModal(true);
    matedit.exec();
}

void Configure::on_pushButton_done_clicked()
{
    double radius = 0.0, outerRadius = 0.0, normalisedRadius = 0.0;
    QString qNormalisedRadius;

    for (int i=0; i<ui->spinBox_nLayers->value(); i++){
        radius = QString(ui->tableWidget_build->item(i,1)->text()).toDouble();
        if (radius > outerRadius){
            outerRadius = radius;
        }
    }

    for (int i=0; i<ui->spinBox_nLayers->value(); i++){
        radius = QString(ui->tableWidget_build->item(i,1)->text()).toDouble();
        normalisedRadius = radius / outerRadius;
        qNormalisedRadius = QString::number(normalisedRadius);
        ui->tableWidget_build->item(i,1)->setText(qNormalisedRadius);
    }

    ofstream config("Configure/config.cfg");
    ofstream structure("Configure/struct.cfg");
    ofstream matList("Configure/matList.txt");

    config << "nPhot " << ui->spinBox_nPhot->value() << endl;
    config << "nLayers " << ui->spinBox_nLayers->value() << endl;
    config << "wavelength " << ui->spinBox_wavelength->value() << endl;
    config << "END" << endl;

    for (int i=0; i<ui->listWidget_add_material->count(); i++){
        QString qName = ui->listWidget_add_material->item(i)->text();
        string name = qName.toUtf8().constData();
        matList << name << endl;
    }

    bool complete = true;
    for (int i=0; i<ui->spinBox_nLayers->value(); i++){
        if (ui->tableWidget_build->item(i,0)->text() == "-"){
            complete = false;
        }
    }

    if (complete == false){
        QMessageBox::warning(this,tr("Warning!"),tr("Planet build is not complete!"));
        return;
    }
    else {
        for (int i=0; i<ui->spinBox_nLayers->value(); i++){
            string name = (ui->tableWidget_build->item(i,0)->text()).toUtf8().constData();
            double radius = QString(ui->tableWidget_build->item(i,1)->text()).toDouble();
            structure << name << " " << radius << endl;
        }
       structure << "END" << endl;
    }

    this->close();
}

void Configure::populateLists(){

    ifstream matList("Configure/matList.txt");

    if (!matList)
        QMessageBox::warning(this,tr("Error!"),tr("Error!\n\nCould not open matList.txt."));

    while (matList){
        string name;
        matList >> name;
        if (name.length() > 1){
            QString qName = QString::fromStdString(name);
            ui->listWidget_add_material->addItem(qName);
            ui->listWidget_known_materials->addItem(qName);
        }
    }

    ui->comboBox_scatter_type->addItem("ISO");
    ui->comboBox_scatter_type->addItem("RAY");
    ui->comboBox_scatter_type->addItem("MIE");

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
        ui->tableWidget_build->setItem(i,1,new QTableWidgetItem(" "));
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
        ui->tableWidget_build->item(row,1)->setText(" ");
        ui->tableWidget_build->item(row,1)->setBackgroundColor(Qt::black);
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

void Configure::on_tableWidget_build_cellClicked()
{
    ui->pushButton_remove->setEnabled(true);
}

void Configure::on_pushButton_add_new_material_clicked(){

    string name = (ui->lineEdit_name->text()).toUtf8().constData();

    if (name.length() < 2){
        QMessageBox::information(this,tr("Too Short"),tr("Failed!\n\nMaterial name is too short."));
        return;
    }

    string path = "Configure/Materials/";
    path += name;
    path += ".mat";

    double kappa = QString(ui->doubleSpinBox_kappa->text()).toDouble();
    double albedo = QString(ui->doubleSpinBox_albedo->text()).toDouble();
    string scatterType = (ui->comboBox_scatter_type->currentText()).toUtf8().constData();

    ofstream mat(path.c_str());

    mat << "kappa " << kappa << endl;
    mat << "albedo " << albedo << endl;
    mat << "scatterType " << scatterType << endl;
    mat << "END" << endl;

    QString qName = ui->lineEdit_name->text();
    ui->listWidget_add_material->addItem(qName);
    ui->listWidget_known_materials->addItem(qName);

    return;
}

void Configure::on_listWidget_known_materials_clicked()
{
    ui->pushButton_edit_material->setEnabled(true);
}



void Configure::on_spinBox_nLayers_valueChanged(int nLayers){

    ui->tableWidget_build->setRowCount(nLayers);

    for (int i=0; i<nLayers; i++){
        ui->tableWidget_build->setItem(i,0,new QTableWidgetItem("-"));
        ui->tableWidget_build->setItem(i,1,new QTableWidgetItem(" "));
    }

    return;
}
