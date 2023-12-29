#ifndef MULTBUFFER_H
#define MULTBUFFER_H
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
//int speed = 10;
// 定义Box类
class Box {
public:
    Box(int capacity) : capacity(capacity), count(0) {}
    void set_capacity(int cp);
    int capacity;
    int count;
    QMutex mutex;
    QWaitCondition notFull;
    QWaitCondition notEmpty;
    int speed = 10;
};

// 定义Worker类
class Worker : public QThread {
//    Q_OBJECT
public:
    Worker(Box *box1, Box *box2 = nullptr) : box1(box1), box2(box2) {}
protected:
    Box *box1;
    Box *box2;
    int speed  = 10;
};

// 定义Worker1类
class Worker1 : public Worker {
public:
    Worker1(Box *box) : Worker(box) {}
    void run() override ;
    int get_speed() {
        return speed;
    }

    void put();
private:
    int speed  = 10;
};

// 定义Worker2类
class Worker2 : public Worker {
public:
    Worker2(Box *box) : Worker(box) {}
    void run() override ;
    int get_speed() {
        return speed;
    }
private:
    int speed  = 10;
};

// 定义Worker3类
class Worker3 : public Worker {
public:
    Worker3(Box *box1, Box *box2, Box *box3) : Worker(box1, box2), box3(box3) {}
    void run() override;
    int get_speed() {
        return speed;
    }

private:
    int speed  = 10;
    Box *box3;
};

// 定义Carrier类
class Carrier : public Worker {
public:
    Carrier(Box *box1) : Worker(box1) {}
    void run() override ;
    int get_speed() {
        return speed;
    }
private:
    int speed  = 10;
};

#endif // MULTBUFFER_H
