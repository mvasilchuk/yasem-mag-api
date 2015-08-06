#ifndef STBUPDATE_H
#define STBUPDATE_H

#include <QObject>

namespace yasem
{
class MagProfile;

namespace SDK {
class WebPage;
}

class StbUpdate : public QObject
{
    Q_OBJECT
public:
    explicit StbUpdate(MagProfile *m_profile, SDK::WebPage* page);

    enum UpdateStatus {
        UNDEFINED = -1,
        CRYPTO_INIT_ERROR = 1,
        WRONG_STB_MODEL = 2,
        NAND_IS_TOO_SMALL = 3,
        NAND_NOT_FOUND = 4,
        KERNEL_UPDATING = 5,
        FIRMWARE_UPDATING = 6,
        INTERNAL_ERROR = 7,
        FIRMWARE_ANALYSING = 8,
        ENV_UPDATING = 9,
        BOOTSTRAP_UPDATING_1 = 10,
        BOOTSTRAP_UPDATING_2 = 11,
        FUSE_UPDATING_1 = 12,
        FUSE_UPDATING_2 = 13,
        SECOND_BOOT_UPDATING = 14,
        LOGO_UPDATING = 15,
        UPDATE_COMPLETE = 16,
        WRONG_SIGNATURE = 17,
        NAND_PREPARING = 18,
        NAND_WRITE_ERROR_1 = 19,
        NAND_WRITE_ERROR_2 = 20,
        FREE = 21,
        WRONG_HEADER = 22,
        VERSION_ANALYSING = 23,
        ANALYSE_COMPLETE = 24,
        FILE_NOT_FOUND = 25,
        PREPARING = 26,
        READ_ERROR = 27,
    };

signals:

public slots:
    int GetFlashBankCount();
    int getStatus();

    int getActiveBank();
    void startCheck(const QString &data);
    int getPercents();
    QString getImageDateStr();
    QString getImageDescStr();
    QString getImageVersionStr();
protected:
    MagProfile* m_profile;
    SDK::WebPage* m_page;

};

}

#endif // STBUPDATE_H
