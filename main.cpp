#include <QtGui/QApplication>
#include <QTextCodec>
#include "artnetconsole.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QApplication app(argc, argv);
    app.setStyle("plastique");
    ArtnetConsole window;
    window.show();

    return app.exec();
}
