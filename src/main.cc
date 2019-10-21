#include <QApplication>

#include "app.h"

int main(int argc, char* argv[])
{
    QApplication qapp(argc, argv);
    App app;
    app.show();
    return qapp.exec();
}