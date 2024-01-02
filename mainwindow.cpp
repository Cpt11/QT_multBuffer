// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MultBuffer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    //定义对象  +  组件添加

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
    slider = new QSlider(this);
    slider->setOrientation(Qt::Horizontal);  // 设置滑块为水平方向
    slider->move(130, 190);
    slider->setRange(200, 2000);  // min和max是你想要设置的最小值和最大值
    slider->setValue(1000);  // initialValue是你想要设置的初始值
    connect(slider, &QSlider::valueChanged, this, &MainWindow::adjustSleepTime1);
    slider->setStyleSheet("QSlider::groove:horizontal {"
                          "border: 1px solid #ff0000;"  // 红色边框
                          "background: #000000;"  // 黑色背景
                          "height: 10px;"
                          "margin: 0 10px;"
                          "}"
                          "QSlider::handle:horizontal {"
                          "background: #ff0000;"  // 红色滑块
                          "border: 1px solid #5c5c5c;"
                          "width: 20px;"
                          "margin: -2px 0;"  // 滑块垂直居中
                          "border-radius: 3px;"
                          "}");

    slider2 = new QSlider(this);
    slider2->setOrientation(Qt::Horizontal);  // 设置滑块为水平方向
    slider2->move(130, 370);
    slider2->setRange(200, 2000);  // min和max是你想要设置的最小值和最大值
    slider2->setValue(1000);  // initialValue是你想要设置的初始值
    connect(slider2, &QSlider::valueChanged, this, &MainWindow::adjustSleepTime2);
    slider2->setStyleSheet("QSlider::groove:horizontal {"
                          "border: 1px solid #ff0000;"  // 红色边框
                          "background: #000000;"  // 黑色背景
                          "height: 10px;"
                          "margin: 0 10px;"
                          "}"
                          "QSlider::handle:horizontal {"
                          "background: #ff0000;"  // 红色滑块
                          "border: 1px solid #5c5c5c;"
                          "width: 20px;"
                          "margin: -2px 0;"  // 滑块垂直居中
                          "border-radius: 3px;"
                          "}");



    slider3 = new QSlider(this);
    slider3->setOrientation(Qt::Horizontal);  // 设置滑块为水平方向
    slider3->move(380, 280);
    slider3->setRange(200, 2000);  // min和max是你想要设置的最小值和最大值
    slider3->setValue(1000);  // initialValue是你想要设置的初始值
    connect(slider, &QSlider::valueChanged, this, &MainWindow::adjustSleepTime3);
    slider3->setStyleSheet("QSlider::groove:horizontal {"
                          "border: 1px solid #ff0000;"  // 红色边框
                          "background: #000000;"  // 黑色背景
                          "height: 10px;"
                          "margin: 0 10px;"
                          "}"
                          "QSlider::handle:horizontal {"
                          "background: #ff0000;"  // 红色滑块
                          "border: 1px solid #5c5c5c;"
                          "width: 20px;"
                          "margin: -2px 0;"  // 滑块垂直居中
                          "border-radius: 3px;"
                          "}");


    slider4 = new QSlider(this);
    slider4->setOrientation(Qt::Horizontal);  // 设置滑块为水平方向
    slider4->move(570, 330);
    slider4->setRange(200, 2000);  // min和max是你想要设置的最小值和最大值
    slider4->setValue(1000);  // initialValue是你想要设置的初始值
    connect(slider4, &QSlider::valueChanged, this, &MainWindow::adjustSleepTime4);
    slider4->setStyleSheet("QSlider::groove:horizontal {"
                          "border: 1px solid #ff0000;"  // 红色边框
                          "background: #000000;"  // 黑色背景
                          "height: 10px;"
                          "margin: 0 10px;"
                          "}"
                          "QSlider::handle:horizontal {"
                          "background: #ff0000;"  // 红色滑块
                          "border: 1px solid #5c5c5c;"
                          "width: 20px;"
                          "margin: -2px 0;"  // 滑块垂直居中
                          "border-radius: 3px;"
                          "}");
    connect(worker3, &Worker3::statusChanged, this, &MainWindow::updateStatus);
    QTimer *timer = new QTimer(this);
    //启动定时器
    timer->start(1000);//500毫秒

    connect(ui->pushButton,&QPushButton::clicked,[=](){
        timer->stop();
    });


    // 启动
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

// MainWindow槽函数
void MainWindow::adjustSleepTime1(int value) {
    worker1->setSleepTime(value);

}

// MainWindow槽函数
void MainWindow::adjustSleepTime2(int value) {
    worker2->setSleepTime(value);
}

// MainWindow槽函数
void MainWindow::adjustSleepTime3(int value) {
    worker3->setSleepTime(value);
}

// MainWindow槽函数
void MainWindow::adjustSleepTime4(int value) {
    carrier->setSleepTime(value);
}

void MainWindow::updateStatus(int count) {
    ui->lineEdit->setText(QString::number(count));
}


