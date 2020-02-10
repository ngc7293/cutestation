#include "data/series_factory.h"

#include "log.h"

#include "data/node_finder.h"
#include "data/time_series.h"
#include "policies/no_sampling_policy.h"

namespace cute { namespace data {

SeriesSP SeriesFactory::build(Tree& tree, const json& config)
{
    SeriesSP series;

    if (config.count("source") != 1) {
        Log::err("SeriesFactory", "'source' is mandatory");
        return series;
    }

    if (!config["source"].is_string()) {
        Log::err("SeriesFactory", "'source' must be a string");
        return series;
    }

    NodeFinder creator(config["source"].get<std::string>(), true);
    NodeSP node = creator.visit(tree.root());

    if (node->series()) {
        return node->series();
    }

    series = std::make_shared<TimeSeries<double>>();
    if (!series->init(std::make_shared<NoSamplingPolicy>(), config)) {
        return series;
    }

    node->setSeries(series);
    return node->series();
}

}} // namespaces