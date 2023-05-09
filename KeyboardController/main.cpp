#include "keyboardcontroller.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KeyboardController w;
    w.show();
    return a.exec();
}
