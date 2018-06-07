#include <iostream>

#include <QApplication>
#include <QFile>
#include <QTextStream>

#include "ui/app.hh"

int main(int argc, char* argv[])
{
    QApplication qapp(argc, argv);
    App app;
    app.show();
    return qapp.exec();
}
