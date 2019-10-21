#include "app.h"

#include <QThread>

#include "../ui/ui_app.h"
#include "displayer.h"

App::App(QWidget* parent)
    : QMainWindow(parent)
    , ui_(new Ui::App())
{
    ui_->setupUi(this);

    Displayer* displayer = new Displayer();
    display_thread_ = new QThread();
    displayer->moveToThread(display_thread_);
    display_thread_->start();
    
    dispatcher_ = new SocketDispatcher(displayer);
    connect(display_thread_, &QThread::finished, displayer, &Displayer::close);

    // FIXME: Find a real icon. This only works on my machine
    setWindowIcon(QIcon("/usr/share/icons/Numix-Circle/48/apps/boostnote.svg"));
}

App::~App()
{
    display_thread_->exit();
    delete dispatcher_;
    delete ui_;
}
