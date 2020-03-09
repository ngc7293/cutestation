#include "data/series_factory.h"

#include "log.h"
#include "util.h"

#include "data/node_finder.h"
#include "data/time_series.h"
#include "policies/no_sampling_policy.h"

namespace cute::data {

SeriesSP SeriesFactory::build(Tree& tree, const json& config)
{
    SeriesSP series;

    if (!has_string(config, "source")) {
        Log::err("SeriesFactory", "missing or invalid configuration 'source'");
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

} // namespaces