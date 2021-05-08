#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Calculator");
    QPixmap icon("Wineass-Ios7-Redesign-Calculator.ico");
    QIcon windowicon(icon);
    w.setWindowIcon(windowicon);
    w.show();
    return a.exec();
}
