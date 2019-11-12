#include "search.h"

#include <algorithm>
#include <cassert>
#include <ctime>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>

#include "../utils.h"

#include "../successor_generators/successor_generator.h"
#include "../heuristics/goalcount.h"

using namespace std;

int Search::getNumberExploredStates() const {
    return number_explored_states;
}

int Search::getNumberGeneratedStates() const {
    return number_generated_states;
}

void Search::extract_goal(int state_counter, int generations, PackedState state,
                          segmented_vector::SegmentedVector<pair<int, Action>> &cheapest_parent,
                          unordered_map<PackedState, int, PackedStateHash> &visited,
                          segmented_vector::SegmentedVector<PackedState> &index_to_state,
                          const StatePacker &packer, const Task &task) const {
    cout << "Goal state found!" << endl;
    cout << "Total number of states visited: " << visited.size() << endl;
    cout << "Total number of states generated: " << generations << endl;
    int packed_state_size = 0;
    for (auto &it : visited) {
        for (auto v : it.first.packed_relations) {
            packed_state_size += estimate_vector_bytes<long>(v.size());
        }
        packed_state_size += estimate_vector_bytes<bool>(it.first.nullary_atoms.size());
        packed_state_size += estimate_vector_bytes<int>(it.first.predicate_symbols.size());
    }
    packed_state_size += estimate_unordered_map_bytes<PackedState, int, PackedStateHash>(visited.size());
    cout << "Size of closed list: " << packed_state_size / 1024 << " kB" <<  endl;
    stack<State> states_in_the_plan;
    states_in_the_plan.push(packer.unpack_state(state));
    while (cheapest_parent[visited[state]].first != -1) {
        state = index_to_state[cheapest_parent[visited[state]].first];
        states_in_the_plan.push(packer.unpack_state(state));
    }
    cout << "Total plan cost: " << states_in_the_plan.size() - 1 << endl;
    /* The section below prints the states on the plan found.
     while (!states_in_the_plan.empty()) {
        state = states_in_the_plan.top();
        cout << "##################" << endl;
        task.dumpState(state);
        states_in_the_plan.pop();
    }*/

}

const int Search::search(const Task &task,
                         SuccessorGenerator *generator,
                         Heuristic &heuristic) const {
    return NOT_SOLVED;
}

void Search::extract_plan(segmented_vector::SegmentedVector<pair<int, Action>> &cheapest_parent, PackedState state,
                                    unordered_map<PackedState, int, PackedStateHash> &visited,
                                    segmented_vector::SegmentedVector<PackedState> &index_to_state,
                                    const StatePacker &packer, const Task &task) {
    vector<Action> actions_in_the_plan;
    while (cheapest_parent[visited[state]].first != -1) {
        actions_in_the_plan.push_back(cheapest_parent[visited[state]].second);
        state = index_to_state[cheapest_parent[visited[state]].first];
    }
    reverse(actions_in_the_plan.begin(), actions_in_the_plan.end());
    ofstream plan_file("sas_plan");
    for (const Action &a : actions_in_the_plan) {
        plan_file << '(' << task.actions[a.index].getName() << " ";
        for (const int obj : a.instantiation) {
            plan_file << task.objects[obj].getName() << " ";
        }
        plan_file << ")\n";
    }
}

