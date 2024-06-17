#ifndef SEARCH_HEURISTICS_WLGOOSE_HEURISTIC_H_
#define SEARCH_HEURISTICS_WLGOOSE_HEURISTIC_H_

#include "datalog_transformation_options.h"
#include "heuristic.h"

#include "../action.h"
#include "../options.h"
#include "../task.h"

#include "../datalog/grounder/weighted_grounder.h"

#include "../ext/wlplan/include/feature_generation/wl_features.hpp"

#include <chrono>
#include <memory>

#define get_time() std::chrono::high_resolution_clock::now().time_since_epoch();


class WlGooseHeuristic : public Heuristic {
protected:
    std::shared_ptr<feature_generation::WLFeatures> model;

    std::chrono::duration<double> start_time, end_time;
    double graph_time;
    double wl_time;
    double linear_time;

public:
    WlGooseHeuristic(const Options &opts, const Task &task);

    void print_statistics() override;

    int compute_heuristic(const DBState &s, const Task &task) override;
};

#endif  // SEARCH_HEURISTICS_WLGOOSE_HEURISTIC_H_
