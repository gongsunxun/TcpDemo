#ifndef COUNTNUMBER_H
#define COUNTNUMBER_H

#include <QObject>
#include <QThread>
#include <QMutex>

class CountNumber : public QThread
{
    Q_OBJECT
public:
    CountNumber();
    ~CountNumber();
    void run();
public slots:
    void SL_startCount();
    void SL_pauseCount();
    void SL_resumeCount();

private:
    int i=0;
    QMutex m_mutex;//互斥量
signals:
    void SG_sendResult(int);//计数结果传到主界面
    void SG_sendFinal(int);//计数最终结果传到主界面

};

#endif // COUNTNUMBER_H
