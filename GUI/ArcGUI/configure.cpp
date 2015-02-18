#include "configure.h"
#include "ui_configure.h"

#include "matedit.h"


Configure::Configure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Configure)
{
    ui->setupUi(this);
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
