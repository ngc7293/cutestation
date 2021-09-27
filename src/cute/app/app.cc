#include <fstream>

#include <nlohmann/json.hpp>

#include <cute/io/dispatcher.hh>
#include <cute/io/dispatcher_factory.hh>

#include "app.hh"
#include "window.hh"
#include "window_factory.hh"

using json = nlohmann::json;

namespace cute {

struct App::priv {
    std::vector<std::shared_ptr<ui::Window>> windows;
    std::vector<std::shared_ptr<io::Dispatcher>> dispatchers;
};

App::App(const std::filesystem::path& config_path)
    : QObject(nullptr)
    , _d(new priv)
{
    std::ifstream ifs(config_path);
    json config = json::parse(ifs, nullptr, true, true);
    _d->windows = ui::WindowFactory::buildAll<ui::Window>(config.at("windows"), nullptr);
    _d->dispatchers = io::DispatcherFactory::buildAll<io::Dispatcher>(config.at("io"));

    for (auto& dispatcher: _d->dispatchers) {
        dispatcher->start();
    }
}

App::~App()
{
    for (auto& dispatcher: _d->dispatchers) {
        dispatcher->close();
    }

    for (auto& windows: _d->windows) {
        windows->hide();
        windows->deleteLater();
    }
}

void App::show()
{
    for (std::shared_ptr<ui::Window>& window: _d->windows) {
        window->show();
    }
}

}