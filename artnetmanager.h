#ifndef ARTNETMANAGER_H
#define ARTNETMANAGER_H

#include <QObject>
#include <QTimer>
#include <artnet/artnet.h>

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
    void initialize(QString ipAddress, int frequency, int universe, bool alwaysBroadcast);
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
