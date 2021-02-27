#include <QApplication>

#include "myequationsystem.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MyEquationSystem system;
    MainWindow window(&system);
    window.show();
    return app.exec();
}
