#ifndef SINGLE_VALUE_WIDGET_H_
#define SINGLE_VALUE_WIDGET_H_

#include "widget.h"

#include <QLabel>

#include "data/time_series.h"

namespace cute::widgets {

class SingleValueWidget : public Widget {
    Q_OBJECT

private:
    data::TimeSeriesSP<double> timeseries_;
    std::uint64_t last_update_;

    QLabel* label_;
    std::string format_;

public:
    SingleValueWidget(QWidget* parent, const std::string& name);
    ~SingleValueWidget() override;

    bool init(const json& config) override;

protected slots:
    void refresh() override;
};

} // namespaces

#endif