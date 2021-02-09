#include "app.hh"

#include <fstream>

#include <nlohmann/json.hpp>

#include <io/dispatcher.hh>
#include <io/dispatcher_factory.hh>

#include "window.hh"
#include "window_factory.hh"

using json = nlohmann::json;

namespace cute {

struct App::priv {
    std::vector<std::shared_ptr<ui::Window>> windows;
    std::vector<std::shared_ptr<io::Dispatcher>> dispatchers;
};

App::App()
    : QObject(nullptr)
    , _d(new priv)
{
    std::ifstream ifs("config.json");
    json config = json::parse(ifs, nullptr, true, true);
    _d->windows = ui::WindowFactory::buildAll<ui::Window>(config.at("windows"), this);
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
}

void App::show()
{
    for (std::shared_ptr<ui::Window>& window: _d->windows) {
        window->show();
    }
}

}