#include "wlgoose_heuristic.h"
#include "../task.h"

#include <cassert>

using namespace std;

WlGooseHeuristic::WlGooseHeuristic(const Options &opts, const Task &task)
{
    // Read paths
    std::string model_path = opts.get_goose_model_path();
    std::string domain_path = opts.get_domain_path();
    std::string problem_path = opts.get_problem_path();

    model = std::make_shared<feature_generation::WLFeatures>(model_path);

    // init timers
    graph_time = 0;
    wl_time = 0;
    linear_time = 0;
}


int WlGooseHeuristic::compute_heuristic(const DBState &s, const Task &task)
{

    // TODO

    return 0;
}

void WlGooseHeuristic::print_statistics()
{
    std::cout << "WlGooseHeuristic graph time: " << graph_time << "s\n";
    std::cout << "WlGooseHeuristic feature time: " << wl_time << "s\n";
    std::cout << "WlGooseHeuristic linear time: " << linear_time << "s\n";
}
