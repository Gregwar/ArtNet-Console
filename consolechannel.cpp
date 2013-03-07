#include <sstream>
#include "consolechannel.h"
#include "ui_consolechannel.h"

using namespace std;

ConsoleChannel::ConsoleChannel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConsoleChannel),
    value(0)
{
    ui->setupUi(this);
    QObject::connect(ui->slider, SIGNAL(valueChanged(int)), this, SLOT(valueChanged(int)));
    QObject::connect(ui->value, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
    valueChanged(0);
}

ConsoleChannel::~ConsoleChannel()
{
    delete ui;
}

void ConsoleChannel::valueChanged(int newValue)
{
    // Updates the value of the channel
    ui->value->setText(QString("%1").arg(newValue));
    ui->slider->setValue(newValue);
    value = newValue;
    changed(channelNumber, newValue);
}

void ConsoleChannel::setChannelNumber(int channelNumber_)
{
    channelNumber = channelNumber_;
    ui->channelName->setText(QString("%1").arg(channelNumber));
}

void ConsoleChannel::textChanged(QString value)
{
    valueChanged(value.toInt());
}

int ConsoleChannel::getValue()
{
    return value;
}
