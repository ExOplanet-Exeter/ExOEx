#ifndef CONFIGURE_H
#define CONFIGURE_H

#include <QDialog>

namespace Ui {
class Configure;
}

class Configure : public QDialog
{
    Q_OBJECT

public:
    explicit Configure(QWidget *parent = 0);
    ~Configure();

private slots:
    void on_pushButton_edit_material_clicked();

    void on_pushButton_done_clicked();

    void populateLists();

    void on_pushButton_add_clicked();

    void on_pushButton_remove_clicked();

private:
    Ui::Configure *ui;
};

#endif // CONFIGURE_H
