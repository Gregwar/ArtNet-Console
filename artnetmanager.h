#ifndef ARTNETMANAGER_H
#define ARTNETMANAGER_H

#include <QObject>
#include <QTimer>
#include <artnet/artnet.h>

#define ARTNETMANAGER_CHANNELS 512

/**
 * Manages the connection with the ArtNet layer, using the libartnet API
 */
class ArtnetManager : public QObject
{
    Q_OBJECT

public:
    ArtnetManager();
    ~ArtnetManager();

    void stop();
    bool initialize(QString ipAddress, int frequency, int universe, bool alwaysBroadcast);
    void updateValue(int channel, int value);
    QString getError();

public slots:
    void tick();

protected:
    QString error;
    char channels[ARTNETMANAGER_CHANNELS];
    int universe;
    QTimer timer;
    artnet_node node;
};

#endif // ARTNETMANAGER_H
