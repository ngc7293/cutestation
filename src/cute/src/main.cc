#include <QApplication>

#include "app.hh"

int main(int argc, char* argv[])
{
    /* App */
    QApplication qapp(argc, argv);
    cute::App app;
    app.show();
    return qapp.exec();
}