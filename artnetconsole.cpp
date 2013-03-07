#include "artnetconsole.h"
#include "ui_artnetconsole.h"

ArtnetConsole::ArtnetConsole(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ArtnetConsole)
{
    ui->setupUi(this);

    // Set up the channel sliders
    for (int i = 0; i < ARTNETMANAGER_CHANNELS; i++) {
        ConsoleChannel *cchannel = new ConsoleChannel(ui->consoleArea);
        cchannel->setChannelNumber(i+1);
        ui->consoleChannels->addWidget(cchannel);
        channels[i+1] = cchannel;
        QObject::connect(cchannel, SIGNAL(changed(int,int)), this, SLOT(changed(int,int)));
    }

    // Connect the ArtNet init button to the initialize slot
    QObject::connect(ui->initButton, SIGNAL(clicked()), this, SLOT(initialize()));
}

ArtnetConsole::~ArtnetConsole()
{
    delete ui;

    // Free all channel sliders
    for (map<int, ConsoleChannel *>::iterator it=channels.begin(); it != channels.end(); it++) {
        delete (*it).second;
    }
}

void ArtnetConsole::initialize()
{
    // Initialize the Art-Net manager
    ui->statusLabel->setStyleSheet("");
    if (ui->enableSending->checkState()) {
        if (manager.initialize(ui->ipAddressField->text(), ui->frequency->text().toInt(), ui->universeField->text().toInt(), ui->alwaysBroadcast->checkState())) {
            ui->statusLabel->setStyleSheet("color: green");
            ui->statusLabel->setText("Art-Net initialized");
        } else {
            ui->statusLabel->setStyleSheet("color: red");
            ui->statusLabel->setText("Art-Net cannot be initialized ("+manager.getError()+")");
        }
    } else {
        manager.stop();
        ui->statusLabel->setText("Disconnected");
    }
}

void ArtnetConsole::changed(int channelNumber, int newValue)
{
    manager.updateValue(channelNumber, newValue);
}
