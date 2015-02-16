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
    void on_pushButton_save_config_clicked();

    void setDefaultValues();

    void populateMatLists();

    void populateBuildList();

    void populateScatterTypes();

    void on_pushButton_add_clicked();

    void on_pushButton_remove_clicked();

    void on_pushButton_save_struct_clicked();

    void on_pushButton_new_mat_clicked();

    void on_pushButton_exit_clicked();

    void on_pushButton_edit_material_clicked();

private:
    Ui::Configure *ui;
};

#endif // CONFIGURE_H
