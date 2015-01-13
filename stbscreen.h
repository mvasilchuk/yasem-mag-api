#ifndef STBSCREEN_H
#define STBSCREEN_H

#include <QObject>

namespace yasem
{
class MagProfile;

class StbScreen : public QObject
{
    Q_OBJECT
public:
    explicit StbScreen(MagProfile *profile);
    Q_PROPERTY(int width READ getWidth USER true)
    Q_PROPERTY(int height READ getHeight USER true)
    Q_PROPERTY(int innerWidth READ getWidth USER true)
    Q_PROPERTY(int innerHeight READ getHeight USER true)
    Q_PROPERTY(int availWidth READ getWidth USER true)
    Q_PROPERTY(int availHeight READ getHeight USER true)
    Q_PROPERTY(int colorDepth READ getColorDepth USER true)
protected:
    int width;
    int height;
    int colorDepth;

    int getWidth() {return width;}
    int getHeight() {return height;}
    int getColorDepth() {return colorDepth;}

     MagProfile* profile;
signals:

};

}
#endif // STBSCREEN_H
