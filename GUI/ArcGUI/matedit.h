#ifndef MATEDIT_H
#define MATEDIT_H

#include <QDialog>

namespace Ui {
class MatEdit;
}

class MatEdit : public QDialog
{
    Q_OBJECT

public:
    explicit MatEdit(QWidget *parent = 0);
    void setName(const QString &labelText);
    ~MatEdit();

private slots:
    void on_pushButton_done_clicked();

private:
    Ui::MatEdit *ui;

    void populateComboBox();
};

#endif // MATEDIT_H
