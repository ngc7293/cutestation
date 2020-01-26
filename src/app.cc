#include "app.h"

#include <iostream>

#include <QLayout>
#include <QThread>

#include "nlohmann/json.hpp"

#include "../ui/ui_app.h"
#include "data/node_finder.h"
#include "data/tree.h"
#include "widgets/chart_widget.h"

App::App(QWidget* parent)
    : QMainWindow(parent)
    , ui_(new Ui::App())
{
    ui_->setupUi(this);

    tree_ = new cute::data::Tree();
    dispatcher_ = new SocketDispatcher(tree_);

    cute::data::NodeFinder("anirniq.mission.charge", true).visit(tree_->root());
    cute::data::NodeFinder("anirniq.mission.status", true).visit(tree_->root());

    Widget* widget_a = new ChartWidget(this, "test widget");
    if (!widget_a->init(cute::data::NodeFinder("anirniq.mission.status").visit(tree_->root())->series(), R"({"refresh_rate": 10})"_json)) {
        std::cerr << "Could not initiate widget_a" << std::endl;
    }
    ui_->gridLayout_2->addWidget(widget_a, 0, 0);

    Widget* widget_b = new ChartWidget(this, "test widget");
    if (!widget_b->init(cute::data::NodeFinder("anirniq.mission.charge").visit(tree_->root())->series(), R"({"refresh_rate": 60})"_json)) {
        std::cerr << "Could not initiate widget_b" << std::endl;
    }
    ui_->gridLayout_2->addWidget(widget_b, 0, 1);

    cute::data::NodeFinder("anirniq.mission.status");

    // FIXME: Find a real icon. This only works on my machine
    setWindowIcon(QIcon("/usr/share/icons/Numix-Circle/48/apps/boostnote.svg"));
}

App::~App()
{
    delete dispatcher_;
    delete tree_;
    delete ui_;
}
