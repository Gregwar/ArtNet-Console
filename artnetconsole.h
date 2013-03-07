#ifndef ARTNETCONSOLE_H
#define ARTNETCONSOLE_H

#include <map>
#include <QMainWindow>
#include "consolechannel.h"
#include "artnetmanager.h"

using namespace std;

namespace Ui {
    class ArtnetConsole;
}

class ArtnetConsole : public QMainWindow
{
    Q_OBJECT

public:
    explicit ArtnetConsole(QWidget *parent = 0);
    ~ArtnetConsole();

public slots:
    void initialize();
    void changed(int channelNumber, int newValue);
    void clear();

private:
    Ui::ArtnetConsole *ui;
    map<int, ConsoleChannel *> channels;
    ArtnetManager manager;
};

#endif // ARTNETCONSOLE_H
