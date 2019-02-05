#include "ui/app.hh"

#include <sstream>
#include "ui/widgets/widget.hh"

#include "ui_app.h"

App::App(QWidget* parent)
    : QMainWindow(parent)
    , ui_(new Ui::App())
{
    ui_->setupUi(this);
    random_ = new RandomWorker();
    QObject::connect(random_, SIGNAL(messageReady(Message*)), this, SLOT(onMessage(Message*)));
    random_->start();

    chart_widget1_ = new ChartWidget();
    chart_widget2_ = new ChartWidget();
    chart_widget3_ = new ChartWidget();
    chart_widget4_ = new ChartWidget();

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
    delete random_;
}

void App::onMessage(Message* message)
{
    *chart_widget1_ << *message;
    *chart_widget2_ << *message;
    *chart_widget3_ << *message;
    *chart_widget4_ << *message;
    delete message;
}