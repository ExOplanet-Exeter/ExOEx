#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    std::string getExOExPathString();
    void showTime();
    void on_pushButton_run_clicked();

    void on_pushButton_configure_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
