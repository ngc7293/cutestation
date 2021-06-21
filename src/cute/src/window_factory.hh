#ifndef CUTE_WINDOW_FACTORY_HH_
#define CUTE_WINDOW_FACTORY_HH_

#include <memory>

#include <QObject>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace cute::ui {

class WindowFactory {
public:
    template<class T>
    static std::shared_ptr<T> build(const json& j, QWidget* parent = nullptr);

    template<class T>
    static std::vector<std::shared_ptr<T>> buildAll(const json& j, QWidget* parent = nullptr);
};

}

#endif