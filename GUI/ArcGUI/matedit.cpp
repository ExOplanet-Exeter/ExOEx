#include "matedit.h"
#include "ui_matedit.h"

#include <fstream>
#include <QMessageBox>

using namespace std;

MatEdit::MatEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MatEdit)
{
    ui->setupUi(this);

    populateComboBox();
}

MatEdit::~MatEdit()
{
    delete ui;
}


void MatEdit::setName(const QString &labelText){

    string name = QString(labelText).toUtf8().constData();

    string path = "Configure/Materials/";
    path += name;
    path += ".mat";

    ifstream mat(path.c_str());

    if (mat == NULL){
        QMessageBox::warning(this,tr("Error!"),tr(".mat file not found.\n\nA new one will be created upon clicking 'done'."));
        ofstream mat(path.c_str());
    }

    string word;
    while (mat){
        mat >> word;
        if (word == "kappa"){
            double kappa;
            mat >> kappa;
            ui->doubleSpinBox_kappa->setValue(kappa);
        }
        else if (word == "albedo"){
            double albedo;
            mat >> albedo;
            ui->doubleSpinBox_albedo->setValue(albedo);
        }
        else if (word == "scatterType"){
            string scatterType;
            mat >> scatterType;
            if (scatterType == "ISO"){
                ui->comboBox_scatter_type->setCurrentIndex(0);
            }
            else if (scatterType == "RAY"){
                ui->comboBox_scatter_type->setCurrentIndex(1);
            }
            else if (scatterType == "MIE"){
                ui->comboBox_scatter_type->setCurrentIndex(2);
            }
        }
    }

    ui->lineEdit_name->setText(labelText);

    return;
}


void MatEdit::populateComboBox(){

    ui->comboBox_scatter_type->addItem("ISO");
    ui->comboBox_scatter_type->addItem("RAY");
    ui->comboBox_scatter_type->addItem("MIE");

    return;
}

void MatEdit::on_pushButton_done_clicked(){

    double kappa = QString(ui->doubleSpinBox_kappa->text()).toDouble();
    double albedo = QString(ui->doubleSpinBox_albedo->text()).toDouble();
    string scatterType = (ui->comboBox_scatter_type->currentText()).toUtf8().constData();

    string name = (ui->lineEdit_name->text()).toUtf8().constData();

    string path = "Configure/Materials/";
    path += name;
    path += ".mat";

    ofstream mat(path.c_str());

    mat << "kappa " << kappa << endl;
    mat << "albedo " << albedo << endl;
    mat << "scatterType " << scatterType << endl;
    mat << "END" << endl;

    return;
}
