#include "app.h"

#include <iostream>

#include <QLayout>
#include <QThread>

#include "../ui/ui_app.h"
#include "data/data_tree.h"
#include "widgets/chart_widget.h"

App::App(QWidget* parent)
    : QMainWindow(parent)
    , ui_(new Ui::App())
{
    ui_->setupUi(this);

    tree_ = new DataTree();
    dispatcher_ = new SocketDispatcher(tree_);

    tree_->root().addChild("anirniq");
    tree_->root().child("anirniq")->addChild("mission");
    tree_->root().child("anirniq")->child("mission")->addChild("charge");

    Widget* widget = new ChartWidget(this, "test widget");
    widget->init(tree_->find("anirniq.mission.charge")->series());
    ui_->gridLayout_2->addWidget(widget, 0, 0);

    // FIXME: Find a real icon. This only works on my machine
    setWindowIcon(QIcon("/usr/share/icons/Numix-Circle/48/apps/boostnote.svg"));
}

App::~App()
{
    delete dispatcher_;
    delete tree_;
    delete ui_;
}
