#include "artnetconsole.h"
#include "ui_artnetconsole.h"

ArtnetConsole::ArtnetConsole(QWidget *parent) :
    QMainWindow(parent),
    sendOnNb(1),
    sendOnEvery(1),
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

    // Connects the ArtNet init button to the initialize slot
    QObject::connect(ui->initButton, SIGNAL(clicked()), this, SLOT(initialize()));
    QObject::connect(ui->disconnectButton, SIGNAL(clicked()), this, SLOT(disconnect()));

    // Connects the Clear button
    QObject::connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clear()));

    // Connects the Send On & Every
    QObject::connect(ui->sendOnNb, SIGNAL(textChanged(QString)), this, SLOT(sendOnNbChanged(QString)));
    QObject::connect(ui->sendOnEvery, SIGNAL(textChanged(QString)), this, SLOT(sendOnEveryChanged(QString)));
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
    if (manager.initialize(ui->ipAddressField->text(), ui->frequency->text().toInt(), ui->universeField->text().toInt(), ui->alwaysBroadcast->checkState())) {
        ui->statusLabel->setStyleSheet("color: green");
        ui->statusLabel->setText("Art-Net initialized");
    } else {
        ui->statusLabel->setStyleSheet("color: red");
        ui->statusLabel->setText("Art-Net cannot be initialized ("+manager.getError()+")");
    }
}


void ArtnetConsole::disconnect()
{
    manager.stop();
    ui->statusLabel->setStyleSheet("");
    ui->statusLabel->setText("Disconnected");
}

void ArtnetConsole::changed(int channelNumber, int newValue)
{
    int i;

    for (i=0; i<sendOnNb; i++) {
        int channel = channelNumber + sendOnEvery*i;
        if (channel > ARTNETMANAGER_CHANNELS) {
            break;
        }
        manager.updateValue(channel, newValue);
        channels[channel]->updateValue(newValue, false);
    }
}

void ArtnetConsole::clear()
{
    for (map<int, ConsoleChannel *>::iterator it=channels.begin(); it != channels.end(); it++) {
        ConsoleChannel *cchannel =(*it).second;
        cchannel->valueChanged(0);
    }
}

void ArtnetConsole::sendOnNbChanged(QString value)
{
    sendOnNb = value.toInt();
    ui->sendOnNb->setText(QString("%1").arg(sendOnNb));
}

void ArtnetConsole::sendOnEveryChanged(QString value)
{
    sendOnEvery = value.toInt();
    ui->sendOnEvery->setText(QString("%1").arg(sendOnEvery));
}

