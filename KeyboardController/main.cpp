#include "keyboardcontroller.h"
#include <QtWidgets/QApplication>

#include "sk108.hpp"

int main(int argc, char *argv[]) {
    Board::SK108::start();
    QApplication a(argc, argv);
    KeyboardController w;
    w.show();
    return a.exec();
}
