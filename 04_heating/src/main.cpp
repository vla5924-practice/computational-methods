#include "mainwindow.h"

#include <QApplication>
#include <QMetaType>

#include "computationresult.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<ComputationResult>("ComputationResult");
    MainWindow w;
    w.show();
    return a.exec();
}
