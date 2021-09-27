#include <util/json.hh>

#include "series_factory.hh"
#include "time_series.hh"

namespace cute::data {

template<>
std::shared_ptr<TimeSeries> SeriesFactory::build(const json& config)
{
    std::shared_ptr<TimeSeries> series;
    std::string source, name;
    uint64_t length;

    bool result = util::json::validate("TimeSeries", config,
        util::json::required(source, "source"),
        util::json::required(length, "length")
    );

    if (!result) {
        return series;
    }

    series = std::make_shared<TimeSeries>(source, std::chrono::milliseconds(length));
    return series;
}

} // namespaces