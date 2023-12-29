#ifndef ML
#define ML

#include <QThread>
#include <QMutex>

class Box {
public:
    Box() : count(0) {}
    int count;
};

class Worker1 : public QThread {
    Q_OBJECT
public:
    Worker1(Box *box) : box(box) {}
    void run() override {
        while (true) {
            mutex.lock();
            box->count++;
            emit boxUpdated(box->count);
            mutex.unlock();
            msleep(1000);
        }
    }
signals:
    void boxUpdated(int count);
private:
    Box *box;
    QMutex mutex;
};

class Worker2 : public QThread {
    Q_OBJECT
public:
    Worker2(Box *box) : box(box) {}
    void run() override {
        while (true) {
            mutex.lock();
                box->count++;
                emit boxUpdated(box->count);
                mutex.unlock();
                msleep(1000);
        }
    }
signals:
    void boxUpdated(int count);
private:
    Box *box;
    QMutex mutex;
};

class Worker3 : public QThread {
    Q_OBJECT
public:
    Worker3(Box *box1, Box *box2, Box *box3) : box1(box1), box2(box2), box3(box3) {}
    void run() override {
        while (true) {
            mutex.lock();
            if (box1->count >= 1 && box2->count >= 2 ) {
                box1->count--;
                box2->count -= 2;
                box3->count++;
                emit boxUpdated(box3->count);
                mutex.unlock();
            } else {
                // 消费者 wait
                mutex.unlock();
                msleep(1000);
            }
        }
    }
signals:
    void boxUpdated(int count);
private:
    Box *box1, *box2, *box3;
    QMutex mutex;
};

class Carrier : public QThread {
     Q_OBJECT
public:
    Carrier(Box *box3) : box3(box3) {}
    void run() override {
        while (true) {
            mutex.lock();
            if (box3->count > 0) {
                box3->count--;
                ccount++;
                emit boxUpdated(ccount);
                mutex.unlock();
            } else {
                mutex.unlock();
                msleep(1000);
            }
        }
    }
signals:
    void boxUpdated(int ccount);
private:
    int ccount = 0;
    Box *box3;
    QMutex mutex;
};

#endif
