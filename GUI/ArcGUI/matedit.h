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
    ~MatEdit();

private:
    Ui::MatEdit *ui;
};

#endif // MATEDIT_H
