#include "mainwindow.h"
#include "MultBuffer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize( 700, 500 );
    w.setWindowTitle("Mult_Buffer");
    w.show();
    return a.exec();
}
