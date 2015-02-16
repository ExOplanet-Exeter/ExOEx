#include "configure.h"
#include "ui_configure.h"
#include "matedit.h"
#include <iostream>
#include <fstream>
#include <QString>
#include <QMessageBox>

#include <unistd.h>
#define GetCurrentDir getcwd

void setDefaultValues();
void populateMatLists();
void populateBuildList();
void populateScatterTypes();

Configure::Configure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Configure)
{
    // ASK TIM ABOUT THIS. SHOULD BE SOME BETTER WAY TO GRAB PATH
    chdir("/Users/FreddyWordingham/Desktop/ExOEx/Arc/");

    ui->setupUi(this);

    this->setWindowTitle("Configuration");

    ui->pushButton_invis->setVisible(false);

    setDefaultValues();

    populateMatLists();
    populateBuildList();
    populateScatterTypes();
}

Configure::~Configure()
{
    delete ui;
}

void Configure::on_pushButton_save_config_clicked()
{
    using namespace std;

    ofstream config("config/config.cfg");

    if (!config)
        cerr << "Could not open config.cfg" << endl;

    int nPhot, nLayers, wavelength;

    nPhot      = ui->spinBox_nPhot->value();
    nLayers    = ui->spinBox_nLayers->value();
    wavelength = ui->spinBox_wavelength->value();

    config << "nPhot " << nPhot << endl;
    config << "nLayers " << nLayers << endl;
    config << "wavelength " << wavelength << endl;

    return;
}

void Configure::on_pushButton_add_clicked()
{
    QString itm = ui->listWidget_mat_list->currentItem()->text();
    ui->listWidget_build->addItem(itm);
}


void Configure::on_pushButton_remove_clicked()
{
    qDeleteAll(ui->listWidget_build->selectedItems());

    return;
}

void Configure::on_pushButton_save_struct_clicked()
{
    using namespace std;

    ofstream structure("config/structure.cfg");

    if (!structure)
        cerr << "Could not open structure.cfg" << endl;

    int nLayers;
    nLayers = ui->spinBox_nLayers->value();

    for (int i=0; i<nLayers; i++){
        QString qMaterial;
        qMaterial = ui->listWidget_build->item(i)->text();
        std::string material = qMaterial.toUtf8().constData();
        structure << material << endl;
    }

    return;
}

void Configure::populateScatterTypes(){

    ui->comboBox_scatter_type->addItem("ISO");
    ui->comboBox_scatter_type->addItem("RAY");
    ui->comboBox_scatter_type->addItem("MIE");

    return;
}

void Configure::on_pushButton_new_mat_clicked()
{
    using namespace std;

    //  Add the new material to the material lists.
    QString matName = ui->lineEdit_name->text();

    ui->listWidget_known_mats->addItem(matName);
    ui->listWidget_mat_list->addItem(matName);


    //  Create a new .mat file for the new material.
    QString qNewMatName;
    string filePath, newMatName;

    qNewMatName = ui->lineEdit_name->text();
    newMatName = qNewMatName.toUtf8().constData();

    filePath = "config/materials/";
    filePath += newMatName;
    filePath += ".mat";

    ofstream newMat(filePath.c_str());

    if (!newMat)
        cerr << "Could not create new material file!" << endl;


    //  Write the parameteres to the new .mat file.
    QString qScatType;
    string scatType;
    double kappa, albedo;

    qScatType = ui->comboBox_scatter_type->currentText();
    scatType = qScatType.toUtf8().constData();
    kappa  = ui->doubleSpinBox_kappa->value();
    albedo = ui->doubleSpinBox_albedo->value();

    newMat << "Kappa " << kappa << endl;
    newMat << "Albedo " << albedo << endl;
    newMat << "Scatter " << scatType << endl;


    //  Add the material name to materialList.txt
    ofstream matList;
    matList.open("config/materialList.txt", std::ios_base::app);

    if (!matList)
        cerr << "Could not open materialList.txt" << endl;

    matList << newMatName << endl;
}


void Configure::populateMatLists(){

    using namespace std;

    ifstream matList("config/materialList.txt");

    if (!matList)
        cerr << "Could not open materialList.txt" << endl;

    while (matList){
        std::string matName;
        matList >> matName;
        if (matName.length() > 1){
            cout << "New mat: " << matName << endl;
            QString qMatName = QString::fromStdString(matName);
            ui->listWidget_mat_list->addItem(qMatName);
            ui->listWidget_known_mats->addItem(qMatName);
        }
    }

    return;
}

void Configure::populateBuildList(){

    using namespace std;

    ifstream structure("config/structure.cfg");

    if (!structure)
        cerr << "Could not open structure.cfg" << endl;

    while (structure){
        std::string matName;
        structure >> matName;
        if (matName.length() > 1){
            cout << "Structure mat: " << matName << endl;
            QString qMatName = QString::fromStdString(matName);
            ui->listWidget_build->addItem(qMatName);
        }
    }

    return;
}

void Configure::on_pushButton_exit_clicked()
{
    using namespace std;

    int configNLayers=0, buildNLayers=-1;

    ifstream config("config/config.cfg");
    ifstream structure("config/structure.cfg");

    if (!config)
        cerr << "Could not open config.cfg" << endl;
    if (!structure)
        cerr << "Could not open structure.cfg" << endl;

    while (config){
                cout << "reading config" << endl;
        std::string word;
        config >> word;
        if (word == "nLayers"){
            config >> configNLayers;
        }
    }
    while (structure){
        cout << "reading struct" << endl;
        std::string word;
        structure >> word;
        buildNLayers++;
    }

    cout << "c=" << configNLayers << " s=" << buildNLayers << endl;

    if (configNLayers != buildNLayers){
        QMessageBox::warning(this,tr("Mismatched Variable!"),tr("nLayers in config.cfg and structure.cfg do not match."));
    }
}

void Configure::setDefaultValues(){

    using namespace std;

    string word;

    //  Remember config.cfg values
    ifstream config("config/config.cfg");

    if (!config)
        QMessageBox::information(this,tr("File not found!"),tr("config.cfg not found.\n\nLocate or create a new one."));
    else{
        int nPhot, nLayers, wavelength;

        while (config){
            config >> word;
            if (word == "nPhot"){
                config >> nPhot;
                ui->spinBox_nPhot->setValue(nPhot);
            }
            else if (word == "nLayers"){
                config >> nLayers;
                ui->spinBox_nLayers->setValue(nLayers);
            }
            else if (word == "wavelength"){
                config >> wavelength;
                ui->spinBox_wavelength->setValue(wavelength);
            }
        }
    }

    return;
}

void Configure::on_pushButton_edit_material_clicked()
{
    matEdit matedit;

    QString matName = ui->listWidget_known_mats->currentItem()->text();
    matedit.setName(matName);

    matedit.setModal(true);
    matedit.exec();
}
