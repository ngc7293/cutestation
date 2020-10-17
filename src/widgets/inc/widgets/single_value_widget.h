#ifndef CUTE_WIDGETS_SINGLE_VALUE_WIDGET_H_
#define CUTE_WIDGETS_SINGLE_VALUE_WIDGET_H_

#include "widget.h"

#include <QLabel>

#include <data/time_series.hh>

namespace cute::widgets {

class SingleValueWidget : public Widget {
    Q_OBJECT

private:
    std::shared_ptr<data::TimeSeries<double>> timeseries_;
    std::uint64_t last_update_;

    QLabel* label_;
    std::string format_;

public:
    SingleValueWidget(QWidget* parent, const std::string& name);
    ~SingleValueWidget() override;

protected slots:
    void refresh() override;
};

} // namespaces

#endif