#include "data/series_factory.h"

#include <log/log.h>
#include <util/util.h>

#include "data/time_series.h"

#include "no_sampling_policy.h"

namespace cute::data {

template <typename T>
std::shared_ptr<Series> SeriesFactory::build(const json& config)
{
    std::shared_ptr<Series> series;

    if (!has<std::string>(config, "source")) {
        Log::err("SeriesFactory", "missing or invalid configuration 'source'");
        return std::shared_ptr<Series>();
    }

    series = std::make_shared<TimeSeries<T>>();
    if (!series->init(std::make_shared<NoSamplingPolicy>(), config)) {
        return std::shared_ptr<Series>();
    }

    return series;
}

template std::shared_ptr<Series> SeriesFactory::build<double>(const json& config);
template std::shared_ptr<Series> SeriesFactory::build<bool>(const json& config);

} // namespaces