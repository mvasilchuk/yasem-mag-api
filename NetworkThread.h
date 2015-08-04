#ifndef NETWORKTHREAD_H
#define NETWORKTHREAD_H

#include <QThread>

namespace yasem
{
class NetworkThread: public QThread
{
public:
    std::function< void () > m_callback;

    void setCallback(std::function< void () > callback)
    {
        this->m_callback = callback;
    }

    // QThread interface
protected:
    void run()
    {
        Q_ASSERT(m_callback);
        m_callback();
    }
};
}

#endif // NETWORKTHREAD_H
