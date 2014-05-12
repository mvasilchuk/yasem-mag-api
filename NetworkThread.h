#ifndef NETWORKTHREAD_H
#define NETWORKTHREAD_H

#include <QThread>

namespace yasem
{
class NetworkThread: public QThread
{
public:
    std::function< void () > callback;

    void setCallback(std::function< void () > callback)
    {
        this->callback = callback;
    }

    // QThread interface
protected:
    void run()
    {
        Q_ASSERT(callback);
        callback();
    }
};
}

#endif // NETWORKTHREAD_H
