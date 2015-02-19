#include "matedit.h"
#include "ui_matedit.h"

MatEdit::MatEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MatEdit)
{
    ui->setupUi(this);
}

MatEdit::~MatEdit()
{
    delete ui;
}


void MatEdit::setName(const QString &matName){

    ui->label_name->setText(matName);

    return;
}
