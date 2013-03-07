#include <QtGui/QApplication>
#include "artnetconsole.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle("plastique");
    ArtnetConsole window;
    window.show();

    return app.exec();
}
