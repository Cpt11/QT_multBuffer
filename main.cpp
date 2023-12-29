#include "mainwindow.h"
#include "MultBuffer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize( 700, 500 );
    w.setWindowTitle("Mult_Buffer");
    Box box1(10), box2(10), box3(10);
    Worker1 worker1(&box1);
    Worker2 worker2(&box2);
    Worker3 worker3(&box1, &box2, &box3);
    Carrier carrier(&box3);
        worker1.start();
        worker2.start();
        worker3.start();
        carrier.start();

    w.show();
    return a.exec();
}
