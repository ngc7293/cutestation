#ifndef CONFIGURATOR_H_
#define CONFIGURATOR_H_

#include <QGridLayout>

#include <nlohmann/json.hpp>

#include "data/tree.h"
#include "widgets/widget.h"

using json = nlohmann::json;

namespace cute {

class Configurator {

private:
    json config_;

public:
    Configurator();
    ~Configurator();

    bool load(std::string file);
    bool configure(QGridLayout& layout);

private:
    bool addToGrid(QGridLayout& layout, widgets::Widget* widget, const json& config);
};

} // namespace

#endif