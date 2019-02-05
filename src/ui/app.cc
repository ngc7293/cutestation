#include "ui/app.hh"

#include <sstream>

#include "ui_app.h"

#include "connection/connectionmanager.hh"
#include "ui/widgets/widget.hh"
#include "distributor.hh"

App::App(QWidget* parent)
    : QMainWindow(parent)
    , ui_(new Ui::App())
{
    ui_->setupUi(this);

    unixconnectionmanager_ = new UnixConnectionManager();

    chart_widget1_ = new ChartWidget();
    chart_widget2_ = new ChartWidget();
    chart_widget3_ = new ChartWidget();
    chart_widget4_ = new ChartWidget();

    Distributor::get().add(chart_widget1_);
    Distributor::get().add(chart_widget2_);
    Distributor::get().add(chart_widget3_);
    Distributor::get().add(chart_widget4_);

    ui_->chart_grid->addWidget(chart_widget1_, 0, 0, 1, 1);
    ui_->chart_grid->addWidget(chart_widget2_, 0, 1, 1, 1);
    ui_->chart_grid->addWidget(chart_widget3_, 1, 0, 1, 1);
    ui_->chart_grid->addWidget(chart_widget4_, 1, 1, 1, 1);

    // FIXME: Find a real icon. This only works on my machine
    setWindowIcon(QIcon("/usr/share/icons/Numix-Circle/48/apps/boostnote.svg"));
}

App::~App()
{
    delete ui_;
    ConnectionManager::get().closeAll();
}

void App::onMessage(Message* message)
{
    *chart_widget1_ << *message;
    *chart_widget2_ << *message;
    *chart_widget3_ << *message;
    *chart_widget4_ << *message;
    delete message;
}
