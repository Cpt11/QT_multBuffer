#ifndef MULTBUFFER_H
#define MULTBUFFER_H
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

// 定义Box类
class Box {
public:
    Box(int capacity) : capacity(capacity), count(0) {}
    int capacity;
    int count;
    QMutex mutex;
    QWaitCondition notFull;
    QWaitCondition notEmpty;
};

// 定义Worker类
class Worker : public QThread {
public:
    Worker(Box *box1, Box *box2 = nullptr) : box1(box1), box2(box2) {}
protected:
    Box *box1;
    Box *box2;
};

// 定义Worker1类
class Worker1 : public Worker {
public:
    Worker1(Box *box) : Worker(box) {}
    void run() override {
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
};

// 定义Worker2类
class Worker2 : public Worker {
public:
    Worker2(Box *box) : Worker(box) {}
    void run() override {
        while (true) {
            box2->mutex.lock();
            if (box2->count == box2->capacity) {
                box2->notFull.wait(&box2->mutex);
            }
            box2->count++;
            box2->notEmpty.wakeAll();
            box2->mutex.unlock();
        }
    }
};

// 定义Worker3类
class Worker3 : public Worker {
public:
    Worker3(Box *box1, Box *box2, Box *box3) : Worker(box1, box2), box3(box3) {}
    void run() override {
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
private:
    Box *box3;
};

// 定义Carrier类
class Carrier : public Worker {
public:
    Carrier(Box *box) : Worker(box) {}
    void run() override {
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
};



#endif // MULTBUFFER_H
