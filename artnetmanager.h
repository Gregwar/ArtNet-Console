#ifndef ARTNETMANAGER_H
#define ARTNETMANAGER_H

#include <QObject>
#include <QTimer>
#include <artnet/artnet.h>

class ArtnetManager : public QObject
{
    Q_OBJECT

public:
    ArtnetManager();
    ~ArtnetManager();

    void stop();
    void initialize(QString ipAddress, int frequency, int universe);
    void updateValue(int channel, int value);

public slots:
    void tick();

protected:
    char channels[255];
    int universe;
    QTimer timer;
    artnet_node node;
};

#endif // ARTNETMANAGER_H
