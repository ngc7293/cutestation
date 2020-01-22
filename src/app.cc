#include "app.h"

#include <iostream>

#include <QLayout>
#include <QThread>

#include "../ui/ui_app.h"
#include "data_tree.h"
#include "widgets/widget.h"

App::App(QWidget* parent)
    : QMainWindow(parent)
    , ui_(new Ui::App())
{
    ui_->setupUi(this);

    DataTree* tree = new DataTree();
    // data_thread_ = new QThread(this);
    // data_thread_->setObjectName("DataThread");

    tree->root().addChild("anirniq");
    tree->root().child("anirniq")->addChild("mission");
    tree->root().child("anirniq")->child("mission")->addChild("charge");

    // tree->moveToThread(data_thread_);
    // data_thread_->start();

    // Widget* widget = new Widget(this, "test widget");
    // widget->init(tree->find("anirniq.mission.charge")->series().get());
    // layout()->addWidget(widget);

    dispatcher_ = new SocketDispatcher(tree);
    // connect(data_thread_, &QThread::finished, tree, &DataTree::deleteLater);

    // FIXME: Find a real icon. This only works on my machine
    setWindowIcon(QIcon("/usr/share/icons/Numix-Circle/48/apps/boostnote.svg"));
}

App::~App()
{
    data_thread_->exit();
    delete dispatcher_;
    delete ui_;
}
