#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MultBuffer.h"
#include <QPropertyAnimation>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowIcon(QIcon("://work.png"));


    ui->chejia->hide();
    QPoint po1 = ui->Worker1->pos();
    qDebug() << po1.x() << " " << po1.y();
    QPoint po2 = ui->Worker2->pos();
    qDebug() << po2.x() << " " << po2.y();
    QPoint po3 = ui->Worker3->pos();
    qDebug() << po3.x() << " " << po3.y();
    QPoint po4 = ui->BB1->pos();
    qDebug() << po4.x() << " " << po4.y();
    QPoint po5= ui->BB2->pos();
    qDebug() << po5.x() << " " << po5.y();
    QPoint po6 = ui->BB3->pos();
    qDebug() << po6.x() << " " << po6.y();
}


void Box::set_capacity(int cp) {
    capacity = cp;
}

void MainWindow::chejia_move() {
//    ui->chejia->hide();
//    ui->chejia->move(130,110);
//    ui->chejia-s
//    QLabel *label = new QLabel("Box1");
//    QPixmap pixmap;
//    pixmap.load("://chejia.png");
//    label->setPixmap(pixmap);
//    label->setGeometry(0, 150, 50, 50);
//    label->show();

//    QPropertyAnimation *animation = new QPropertyAnimation(ui->chejia, "pos");

    // 设置动画的起始和结束值
//    animation->setStartValue(QPoint(0, 0));
//    animation->setEndValue(QPoint(100, 130));

//    // 设置动画的持续时间
//    animation->setDuration(100000);  // 1000毫秒 = 1秒

//    // 开始动画
//    animation->start();
//qDebug() << 1 ;
}


void Worker1::put() {
    MainWindow mw = new::MainWindow();
    mw.chejia_move();
}

void Worker1::run() {
    while (true) {
        box1->mutex.lock();
        if (box1->count == box1->capacity) {
            box1->notFull.wait(&box1->mutex);
        }
        Worker1::put();

        box1->count++;
        box1->notEmpty.wakeAll();
        box1->mutex.unlock();
    }
}

void Worker2::run()  {
    while (true) {
        box1->mutex.lock();
        if (box1->count == box1->capacity) {
            box1->notFull.wait(&box1->mutex);
        }
        box1->count++;
        box1->notEmpty.wakeAll();
        box1->mutex.unlock();
    }
}

void Worker3::run() {
    while (true) {
        box1->mutex.lock();
        if (box1->count == 0) {
            box1->notEmpty.wait(&box1->mutex);
        }
        box1->count--;
        box1->notFull.wakeAll();
        box1->mutex.unlock();

        box2->mutex.lock();
        if (box2->count < 2) {
            box2->notEmpty.wait(&box2->mutex);
        }
        box2->count -= 2;
        box2->notFull.wakeAll();
        box2->mutex.unlock();

        box3->mutex.lock();
        if (box3->count == box3->capacity) {
            box3->notFull.wait(&box3->mutex);
        }
        box3->count++;
        box3->notEmpty.wakeAll();
        box3->mutex.unlock();
    }
}

void Carrier::run()  {
    while (true) {
        box1->mutex.lock();
        if (box1->count == 0) {
            box1->notEmpty.wait(&box1->mutex);
        }
        box1->count--;
        box1->notFull.wakeAll();
        box1->mutex.unlock();
    }
}


MainWindow::~MainWindow() {
    delete ui;
}

