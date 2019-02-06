#include <iostream>

#include <QApplication>

#include "ui/app.hh"

int main(int argc, char* argv[])
{
    QApplication qapp(argc, argv);
    qapp.setStyleSheet("QWidget { border: 1px solid red }");
    App app;
    app.show();
    return qapp.exec();
}