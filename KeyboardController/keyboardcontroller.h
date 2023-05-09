#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_keyboardcontroller.h"

class KeyboardController : public QMainWindow
{
    Q_OBJECT

public:
    KeyboardController(QWidget *parent = nullptr);
    ~KeyboardController();

private:
    Ui::KeyboardControllerClass ui;
};
