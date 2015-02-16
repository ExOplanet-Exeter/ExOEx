#include "matedit.h"
#include "ui_matedit.h"
#include <fstream>
#include <iostream>

void populateScatterTypes();
void setValues();

matEdit::matEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::matEdit)
{
    // ASK TIM ABOUT THIS. SHOULD BE SOME BETTER WAY TO GRAB PATH
    chdir("/Users/freddy/Desktop/ExOEx/Arc/");

    ui->setupUi(this);

    this->setWindowTitle("Material Edit");

    ui->lineEdit_name->setEnabled(false);

    populateScatterTypes();
    setValues();
}

matEdit::~matEdit()
{
    delete ui;
}

void matEdit::populateScatterTypes(){

    ui->comboBox_scatter_type->addItem("ISO");
    ui->comboBox_scatter_type->addItem("RAY");
    ui->comboBox_scatter_type->addItem("MIE");

    return;
}

void matEdit::setValues(){

    using namespace std;

    QString qScatType, qName;
    string scatType, name, filePath, word;
    double kappa, albedo;

    qName = ui->lineEdit_name->text();
    name = qName.toUtf8().constData();

    filePath = "config/materials/";
    filePath += name;
    filePath += ".mat";

    cout << "Name of mat: " << name << endl;

    ifstream mat(filePath.c_str());

    if (!mat)
        cerr << "Could not edit material file!" << endl;

    while (mat){
        mat >> word;
        cout << "wrd: " << word << endl;
        /*
        if (word == "Kappa"){
            mat >> kappa;
            cout << "Kappa = " << kappa << endl;
            ui->doubleSpinBox_kappa->setValue(kappa);
        }
        else if (word == "Albedo"){
            mat >> albedo;
            cout << "Albedo = " << albedo << endl;
            ui->doubleSpinBox_albedo->setValue(albedo);
        }*/
    }

    return;
}

void matEdit::setName(const QString &labelText){

    ui->lineEdit_name->setText(labelText);

    return;
}

void matEdit::on_pushButton_done_clicked()
{
    using namespace std;

    QString qScatType, qName;
    string scatType, name, filePath;
    double kappa, albedo;

    qName = ui->lineEdit_name->text();
    name = qName.toUtf8().constData();
    qScatType = ui->comboBox_scatter_type->currentText();
    scatType = qScatType.toUtf8().constData();
    kappa = ui->doubleSpinBox_kappa->value();
    albedo = ui->doubleSpinBox_albedo->value();

    cout << "Edited information reads:" << endl;
    cout << "k=" << kappa << " a=" << albedo << " s=" << scatType << endl;
    cout << "name: " << name << endl;

    filePath = "config/materials/";
    filePath += name;
    filePath += ".mat";

    ofstream mat(filePath.c_str());

    if (!mat)
        cerr << "Could not edit material file!" << endl;

    mat << "Kappa " << kappa << endl;
    mat << "Albedo " << albedo << endl;
    mat << "Scatter " << scatType << endl;
}

void matEdit::on_pushButton_update_clicked()
{

    using namespace std;

    QString qScatType, qName;
    string scatType, name, filePath, word;
    double kappa, albedo;

    qName = ui->lineEdit_name->text();
    name = qName.toUtf8().constData();

    filePath = "config/materials/";
    filePath += name;
    filePath += ".mat";

    cout << "Name of mat: " << name << endl;

    ifstream mat(filePath.c_str());

    if (!mat)
        cerr << "Could not edit material file!" << endl;

    while (mat){
        mat >> word;
        cout << "wrd: " << word << endl;

        if (word == "Kappa"){
            mat >> kappa;
            ui->doubleSpinBox_kappa->setValue(kappa);
        }
        else if (word == "Albedo"){
            mat >> albedo;
            ui->doubleSpinBox_albedo->setValue(albedo);
        }
        else if (word == "Scatter"){
            mat >> scatType;
            qScatType = QString::fromStdString(scatType);
            ui->comboBox_scatter_type->setCurrentText(qScatType);
        }
    }

    return;
}
