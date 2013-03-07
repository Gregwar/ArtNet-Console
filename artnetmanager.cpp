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

void ArtnetManager::initialize(QString ipAddress, int frequency, int universe_)
{
    const char *ipAddr = NULL;

    timer.stop();
    if (node != NULL) {
        artnet_stop(node);
        artnet_destroy(node);
    }
    node = NULL;
    universe = universe_;

    if (!ipAddress.isEmpty()) {
        ipAddr = ipAddress.toStdString().c_str();
    }

    node = artnet_new(ipAddr, 0);
    artnet_set_short_name(node, "ArtNet console");
    artnet_set_long_name(node, "ArtNet console");
    artnet_set_node_type(node, ARTNET_SRV);
    artnet_set_bcast_limit(node, 10);

    artnet_set_port_type(node, 0, ARTNET_ENABLE_INPUT, ARTNET_PORT_DMX);
    artnet_set_port_addr(node, 0, ARTNET_INPUT_PORT, universe);

    if (artnet_start(node) == ARTNET_EOK) {
        artnet_send_poll(node, NULL, ARTNET_TTM_DEFAULT);
        timer.start(1000/frequency);
    }
}

void ArtnetManager::tick()
{
    artnet_read(node, 0);
    artnet_send_dmx(node, 0, sizeof(channels), (const uint8_t*)channels);
}

void ArtnetManager::updateValue(int channel, int value)
{
    channels[channel-1] = value;
}
