#ifndef CONSOLECHANNEL_H
#define CONSOLECHANNEL_H

#include <QWidget>

namespace Ui {
    class ConsoleChannel;
}

class ConsoleChannel : public QWidget
{
    Q_OBJECT

public:
    explicit ConsoleChannel(QWidget *parent = 0);
    ~ConsoleChannel();

    void setChannelNumber(int channelNumber);

    int getValue();

public slots:
    void valueChanged(int newValue);
    void textChanged(QString value);

signals:
    void changed(int channelNumber, int newValue);

private:
    int channelNumber;
    int value;
    Ui::ConsoleChannel *ui;
};

#endif // CONSOLECHANNEL_H
