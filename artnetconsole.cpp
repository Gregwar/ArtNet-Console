#include "artnetconsole.h"
#include "ui_artnetconsole.h"

ArtnetConsole::ArtnetConsole(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ArtnetConsole)
{
    ui->setupUi(this);

    for (int i = 0; i < 255; i++) {
        ConsoleChannel *cchannel = new ConsoleChannel(ui->consoleArea);
        cchannel->setChannelNumber(i+1);
        ui->consoleChannels->addWidget(cchannel);
        channels[i+1] = cchannel;
        QObject::connect(cchannel, SIGNAL(changed(int)), this, SLOT(changed(int)));
    }

    QObject::connect(ui->initButton, SIGNAL(clicked()), this, SLOT(initialize()));
}

ArtnetConsole::~ArtnetConsole()
{
    delete ui;

    for (map<int, ConsoleChannel *>::iterator it=channels.begin(); it != channels.end(); it++) {
        delete (*it).second;
    }
}

void ArtnetConsole::initialize()
{
    if (ui->enableSending->checkState()) {
        manager.initialize(ui->ipAddressField->text(), ui->frequency->text().toInt(), ui->universeField->text().toInt());
    } else {
        manager.stop();
    }
}

void ArtnetConsole::changed(int channelNumber)
{
    manager.updateValue(channelNumber, channels[channelNumber]->getValue());
}
