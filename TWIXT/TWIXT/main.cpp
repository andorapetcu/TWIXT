#include "TWIXT.h"
#include "ui_TWIXT.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TWIXT w;
    w.show();
    return a.exec();
}
