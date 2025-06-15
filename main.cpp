#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    // styleName: default,Windows,WindowsVista,Fusion,
    QApplication::setStyle("Fusion");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
