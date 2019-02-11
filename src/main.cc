#include <iostream>

#include <QApplication>

#include "ui/app.hh"

int main(int argc, char* argv[])
{
    QApplication qapp(argc, argv);
    App app;
    app.show();
    return qapp.exec();
}