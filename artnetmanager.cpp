#include <iostream>
#include <artnet/artnet.h>
#include "artnetmanager.h"

using namespace std;

ArtnetManager::ArtnetManager() : node(NULL)
{
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));

    for (int i=0; i<sizeof(channels); i++) {
        channels[i] = 0;
    }
}

ArtnetManager::~ArtnetManager()
{
    artnet_destroy(node);
}

void ArtnetManager::stop()
{
    timer.stop();
    if (node != NULL) {
        artnet_stop(node);
        artnet_destroy(node);
        node = NULL;
    }
}

bool ArtnetManager::initialize(QString ipAddress, int frequency, int universe_, bool alwaysBroadcast)
{
    const char *ipAddr = NULL;

    stop();
    node = NULL;
    universe = universe_;

    // The IP address should be NULL for ArtNet if we don't have
    // any preferred IP
    if (!ipAddress.isEmpty()) {
        ipAddr = ipAddress.toStdString().c_str();
    }

    // Create and name the node
    node = artnet_new(ipAddr, 0);
    artnet_set_short_name(node, "ArtNet console");
    artnet_set_long_name(node, "ArtNet console");

    // This is a server
    artnet_set_node_type(node, ARTNET_SRV);

    // Sets the broadcast limit, regarding the flag
    if (alwaysBroadcast) {
        artnet_set_bcast_limit(node, 0);
    } else {
        artnet_set_bcast_limit(node, 10);
    }

    // Configuring the port
    artnet_set_port_type(node, 0, ARTNET_ENABLE_INPUT, ARTNET_PORT_DMX);
    artnet_set_port_addr(node, 0, ARTNET_INPUT_PORT, universe);

    // Initializing the node and force the polling
    if (artnet_start(node) == ARTNET_EOK) {
        artnet_send_poll(node, NULL, ARTNET_TTM_DEFAULT);
        timer.start(1000/frequency);
        return true;
    } else {
        error = QString(artnet_strerror());
    }

    return false;
}

QString ArtnetManager::getError()
{
    return error;
}

void ArtnetManager::tick()
{
    // Reading ArtNet available data
    artnet_read(node, 0);

    // Sending dmx datas to all channels
    artnet_send_dmx(node, 0, sizeof(channels), (const uint8_t*)channels);
}

void ArtnetManager::updateValue(int channel, int value)
{
    channels[channel-1] = value;
}
