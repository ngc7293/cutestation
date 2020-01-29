#include "app.h"

#include <iostream>

#include <QLayout>
#include <QThread>

#include "nlohmann/json.hpp"

#include "../ui/ui_app.h"
#include "configurator.h"
#include "data/tree.h"

App::App(QWidget* parent)
    : QMainWindow(parent)
    , ui_(new Ui::App())
{
    ui_->setupUi(this);

    tree_ = new cute::data::Tree();
    dispatcher_ = new SocketDispatcher(tree_);

    cute::Configurator configurator;
    configurator.load("config.json");
    configurator.configure(*ui_->gridLayout_2, *tree_);

    // cute::data::NodeFinder("anirniq.mission.charge", true).visit(tree_->root());
    // cute::data::NodeFinder("anirniq.mission.status", true).visit(tree_->root());

    // cute::widgets::Widget* widget_a = new cute::widgets::ChartWidget(this, "test widget");
    // if (!widget_a->init(cute::data::NodeFinder("anirniq.mission.status").visit(tree_->root())->series(), R"({"refresh_rate": 10})"_json)) {
    //     std::cerr << "Could not initiate widget_a" << std::endl;
    // }
    // ui_->gridLayout_2->addWidget(widget_a, 0, 0);

    // cute::widgets::Widget* widget_b = new cute::widgets::ChartWidget(this, "test widget");
    // if (!widget_b->init(cute::data::NodeFinder("anirniq.mission.charge").visit(tree_->root())->series(), R"({"refresh_rate": 60})"_json)) {
    //     std::cerr << "Could not initiate widget_b" << std::endl;
    // }
    // ui_->gridLayout_2->addWidget(widget_b, 0, 1);

    // FIXME: Find a real icon. This only works on my machine
    setWindowIcon(QIcon("/usr/share/icons/Numix-Circle/48/apps/boostnote.svg"));
}

App::~App()
{
    delete dispatcher_;
    delete tree_;
    delete ui_;
}
