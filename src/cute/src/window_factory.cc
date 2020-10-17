#include "window_factory.hh"

#include <QMainWindow>
#include <QString>

#include <util/json.hh>
#include <widgets/widget_factory.h>

#include "window.hh"

namespace cute::ui {

template<>
std::shared_ptr<Window> WindowFactory::build<Window>(const json& config, QObject* parent)
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

    if (util::json::has_array(config, "widgets")) {
        for (const json& el : config.at("widgets")) {
            widgets::Widget* widget = widgets::WidgetFactory::build<widgets::Widget>(el, window.get());

            unsigned x, y, rowspan, colspan;
            int width, height;

            if (widget && util::json::validate("Widget", el,
                util::json::required {x, "x"},
                util::json::required {y, "y"},
                util::json::optionnal {rowspan, "rowspan", 1u},
                util::json::optionnal {colspan, "colspan", 1u},
                util::json::optionnal {width, "width", -1},
                util::json::optionnal {height, "height", -1}
            )) {
                window->addWidget(widget, x, y, rowspan, colspan);

                if (width > 0) {
                    widget->setFixedWidth(width);
                }

                if (height > 0) {
                    widget->setFixedHeight(height);
                }
            }
        }
    }

    return window;
}

template<>
std::vector<std::shared_ptr<Window>> WindowFactory::buildAll<Window>(const json& config, QObject* parent)
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