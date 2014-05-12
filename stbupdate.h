#ifndef STBUPDATE_H
#define STBUPDATE_H

#include <QObject>

namespace yasem
{
class MagProfile;

class StbUpdate : public QObject
{
    Q_OBJECT
public:
    explicit StbUpdate(MagProfile *profile);

signals:

public slots:
    int GetFlashBankCount();
    int getStatus();

    int getActiveBank();
protected:
    MagProfile* profile;

};

}

#endif // STBUPDATE_H
