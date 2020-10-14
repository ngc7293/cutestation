#include "data/series_factory.hh"

#include <log/log.hh>
#include <util/json.hh>

#include "data/time_series.hh"

namespace cute::data {

template<>
std::shared_ptr<TimeSeries<double>> SeriesFactory::build(const json& config)
{
    std::shared_ptr<TimeSeries<double>> series;
    std::string source, name;
    uint64_t length;

    bool result = util::json::validate(config,
        util::json::required(source, "source"),
        util::json::required(length, "length")
    );

    if (result) {
        return series;
    }

    series = std::make_shared<TimeSeries<double>>(source, length);
    return series;
}

} // namespaces