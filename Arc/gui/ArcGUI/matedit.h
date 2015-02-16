#ifndef MATEDIT_H
#define MATEDIT_H

#include <QDialog>

namespace Ui {
class matEdit;
}

class matEdit : public QDialog
{
    Q_OBJECT

public:
    explicit matEdit(QWidget *parent = 0);
    void setName(const QString &labelText);
    ~matEdit();

private slots:
    void on_pushButton_done_clicked();
    void setValues();

    void on_pushButton_update_clicked();

private:
    Ui::matEdit *ui;

    void populateScatterTypes();
};

#endif // MATEDIT_H
