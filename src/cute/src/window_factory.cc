#include "window_factory.hh"

#include <QMainWindow>
#include <QGridLayout>
#include <QString>

#include <util/json.hh>
#include <widgets/widget_factory.hh>

#include "window.hh"

namespace cute::ui {

template<>
std::shared_ptr<Window> WindowFactory::build<Window>(const json& config, QWidget* parent)
{
    std::shared_ptr<Window> window;

    std::string name;

    if (!util::json::validate("Window", config,
        util::json::optionnal {name, "name", "CuteStation"}
    )) {
        return window; // Empty pointer
    }

    window = std::make_shared<Window>(parent);
    window->setWindowTitle(QString::fromStdString(name));

    widgets::WidgetFactory::buildAll(config["widgets"], window->grid(), window.get());

    return window;
}

template<>
std::vector<std::shared_ptr<Window>> WindowFactory::buildAll<Window>(const json& config, QWidget* parent)
{
    std::vector<std::shared_ptr<Window>> windows;

    if (!config.is_array()) {
        return windows;
    }

    for (const json& el: config) {
        if (std::shared_ptr<Window> window = build<Window>(el, parent)) {
            windows.push_back(window);
        }
    }

    return windows;
}

}