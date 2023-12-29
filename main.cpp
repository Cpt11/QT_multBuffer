#include "mainwindow.h"

#include <QApplication>
#include <QTimer>
#include <QPushButton>
#include <QObject>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize( 700, 500 );
    w.setWindowTitle("Mult_Buffer");
    w.setWindowIcon(QIcon("://work"));
    // 创建一个定时器
    w.show();
    return a.exec();
}
