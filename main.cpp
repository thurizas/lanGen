#include "langen.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LanGen w;
    w.show();
    return a.exec();
}
