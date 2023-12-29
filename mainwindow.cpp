// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MultBuffer.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    box1 = new Box();
    box2 = new Box();
    box3 = new Box();
    worker1 = new Worker1(box1);
    worker2 = new Worker2(box2);
    worker3 = new Worker3(box1, box2, box3);
    carrier = new Carrier(box3);
    connect(worker1, &Worker1::boxUpdated, this, &MainWindow::updateBoxCount1);
    connect(worker2, &Worker2::boxUpdated, this, &MainWindow::updateBoxCount2);
    connect(worker3, &Worker3::boxUpdated, this, &MainWindow::updateBoxCount3);
    connect(carrier, &Carrier::boxUpdated, this, &MainWindow::updateBoxCount4);
    worker1->start();
    worker2->start();
    worker3->start();
    carrier->start();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateBoxCount1(int count) {
//    qDebug() << 1 ;
    ui->Box1lineEdit->setText(QString::number(count));
}

void MainWindow::updateBoxCount2(int count) {
    ui->Box2lineEdit->setText(QString::number(count));
}

void MainWindow::updateBoxCount3(int count) {
    ui->Box3lineEdit->setText(QString::number(count));
}

void MainWindow::updateBoxCount4(int count) {
    ui->CarrierlineEdit->setText(QString::number(count));
}
