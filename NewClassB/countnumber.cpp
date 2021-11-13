#include "countnumber.h"

#include <QDebug>
CountNumber::CountNumber()
{

}

CountNumber::~CountNumber()
{

}

void CountNumber::run()
{
    while(1){
        m_mutex.lock();
        i++;
        emit SG_sendResult(i);
        m_mutex.unlock();
        this->msleep(1);

    }
}

void CountNumber::SL_startCount()
{
    this->start();
}

void CountNumber::SL_resumeCount()
{
    this->m_mutex.unlock();
}

void CountNumber::SL_pauseCount()
{
    this->m_mutex.lock();
    emit SG_sendFinal(i);
}
