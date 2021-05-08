#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void number_button_clicked();
    void on_pushButton_Del_clicked();

    void on_pushButton_AC_clicked();

    void on_pushButton_dec_clicked();

    void operators_clicked();

    void on_pushButton_calc_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
