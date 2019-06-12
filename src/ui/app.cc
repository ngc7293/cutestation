#include "ui/app.hh"

#include <fstream>
#include <iostream>

#include "lib/rapidjson/document.h"
#include "lib/rapidjson/istreamwrapper.h"

#include "ui_app.h"

#include "connection/connectionmanager.hh"
#include "distributor.hh"
#include "widgets/chartwidget.hh"
#include "widgets/config/widget_config.hh"
#include "widgets/textwidget.hh"
#include "widgets/widget.hh"

App::App(QWidget* parent)
    : QMainWindow(parent)
    , ui_(new Ui::App())
{
    ui_->setupUi(this);

    unixconnectionmanager_ = new UnixConnectionManager();

    std::ifstream ifs("config.json");
    rapidjson::IStreamWrapper isw(ifs);
    rapidjson::Document config;
    config.ParseStream(isw);

    for (rapidjson::SizeType i = 0; i < config["widgets"].Size(); i++) {
        if (!config["widgets"][i].IsObject()) {
            continue;
        }
        if (config["widgets"][i]["type"] == "chart") {
            ChartWidget* widget_ = new ChartWidget();
            Distributor::get().add(widget_);
            widget_->config()->parse(config["widgets"][i]);

            ui_->chart_grid->addWidget(widget_,
                config["widgets"][i]["pos"]["y"].GetInt(), config["widgets"][i]["pos"]["x"].GetInt(),
                config["widgets"][i]["pos"]["height"].GetInt(), config["widgets"][i]["pos"]["width"].GetInt());
        } else if (config["widgets"][i]["type"] == "text") {
            TextWidget* widget_ = new TextWidget();
            Distributor::get().add(widget_);
            widget_->config()->parse(config["widgets"][i]);

            ui_->chart_grid->addWidget(widget_,
                config["widgets"][i]["pos"]["y"].GetInt(), config["widgets"][i]["pos"]["x"].GetInt(),
                config["widgets"][i]["pos"]["height"].GetInt(), config["widgets"][i]["pos"]["width"].GetInt());
        } else {
            std::cerr << "Unknown widget type " << config["widgets"][i]["type"].GetString() << std::endl;
        }
    }

    // FIXME: Find a real icon. This only works on my machine
    setWindowIcon(QIcon("/usr/share/icons/Numix-Circle/48/apps/boostnote.svg"));
}

App::~App()
{
    delete ui_;
    ConnectionManager::get().closeAll();
}
