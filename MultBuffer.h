#ifndef ML
#define ML

#include <QThread>
#include <QMutex>



class Box {
public:
    Box() : count(0), blockedThreads(0) {}
    int count;
    int blockedThreads;
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
            msleep(sleepTime);
        }
    }
    void setSleepTime(int time) { sleepTime = time; }
signals:
    void boxUpdated(int count);
private:
    int sleepTime = 1000;
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
                msleep(sleepTime);
        }
    }
    void setSleepTime(int time) { sleepTime = time; }
signals:
    void boxUpdated(int count);
private:
    Box *box;
    int sleepTime = 1000;
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
                box3->blockedThreads--;
                emit boxUpdated(box3->count);
                emit statusChanged(box3->blockedThreads);
                mutex.unlock();
            } else {
                msleep(sleepTime);
                box3->blockedThreads++;
                mutex.unlock();
            }
        }
    }
    void setSleepTime(int time) { sleepTime = time; }
signals:
    void statusChanged(int count);
    void boxUpdated(int count);
private:
    Box *box1, *box2, *box3;
    int sleepTime = 1000;
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
                msleep(sleepTime);
                box3->blockedThreads--;
                mutex.unlock();
            } else {
                msleep(sleepTime);
                box3->blockedThreads++;
                 mutex.unlock();
            }
        }
    }
    void setSleepTime(int time) { sleepTime = time; }
signals:
    void boxUpdated(int ccount);
private:
    int sleepTime = 1000;
    int ccount = 0;
    Box *box3;
    QMutex mutex;
};

#endif
