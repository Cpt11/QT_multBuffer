// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "MultBuffer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void updateBoxCount1(int count);
    void updateBoxCount2(int count);
    void updateBoxCount3(int count);
    void updateBoxCount4(int count);
private:
    Ui::MainWindow *ui;
    Box *box1, *box2, *box3;
    Worker1 *worker1;
    Worker2 *worker2;
    Worker3 *worker3;
    Carrier *carrier;
};

#endif // MAINWINDOW_H
