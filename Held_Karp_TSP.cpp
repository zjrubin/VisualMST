#include "Held_Karp_TSP.h"
#include <cassert>
#include <limits>

using std::istream;
using std::numeric_limits;
using std::set;
using std::vector;

template<typename T>
bool Held_Karp_TSP::Set_Comp<T>::operator() (const set<T>& lhs, const set<T>& rhs) const
{
    if (lhs.size() != rhs.size())
        return lhs.size() < rhs.size();

    for (auto iter1 = lhs.begin(), iter2 = rhs.begin(); iter1 != lhs.end(); ++iter1, ++iter2)
    {
        if (*iter1 != *iter2)
            return *iter1 < *iter2;
    }

    assert(!"This point shold not be reached");
    return false;
}


bool Held_Karp_TSP::Comp_Path::operator() (const Path& lhs, const Path& rhs) const
{
    if (lhs.previous_vertices.size() != rhs.previous_vertices.size())
        return lhs.previous_vertices.size() < rhs.previous_vertices.size();

    if (lhs.vertex_to != rhs.vertex_to)
        return lhs.vertex_to < rhs.vertex_to;

    auto& lprev = lhs.previous_vertices;
    auto& rprev = rhs.previous_vertices;
    for (auto iter1 = lprev.begin(), iter2 = rprev.begin(); iter1 != lprev.end(); ++iter1, ++iter2)
    {
        if (*iter1 != *iter2)
            return *iter1 < *iter2;
    }

    return false; // lhs !< rhs
}


Held_Karp_TSP::Held_Karp_TSP(istream& is)
    : Graph{ is }
{
    Adjacency_matrix_t edge_weights = create_adjacency_matrix();

    // Create every possible subset of verticies in the graph, excluding vertex 0
    Power_Set_t powerset = generate_power_set(verticies.size() - 1);

    // Apply the Held-Karp algorithm
    Paths_container_t paths = generate_paths(edge_weights, powerset);
    
    // Sum of all the edge weights is stored in [0, {all other verticies}]
    total_edge_weight = paths[{0, *powerset.rbegin()}];

    // Find all the edges used to complete the TSP
    trace_path(paths, edge_weights, *powerset.rbegin());
}


Held_Karp_TSP::Power_Set_t Held_Karp_TSP::generate_power_set(int n)
{
    Power_Set_t powerset;
    vector<int> stack(n + 1, 0);
    int k = 0;

    while (true)
    {
        if (stack[k] < n)
        {
            stack[k + 1] = stack[k] + 1;
            k++;
        }
        else
        {
            stack[k - 1]++;
            k--;
        }

        if (k == 0)
            break;

        powerset.emplace(stack.begin() + 1, stack.begin() + k + 1);
        Set_t tmp(stack.begin() + 1, stack.begin() + k + 1);
    }

    // Add the null set
    powerset.emplace();

    return powerset;
}


Held_Karp_TSP::Paths_container_t Held_Karp_TSP::generate_paths(const Adjacency_matrix_t& edge_weights, const Power_Set_t& powerset)
{
    Paths_container_t paths;
    // Iterate from the null set through every subset, but exclude the full set itself
    for (auto iter = powerset.begin(); iter != powerset.end(); ++iter)
    {
        // calculate distance back to starting vertex
        if (iter->size() == verticies.size() - 1)
        {
            find_distance(paths, edge_weights, 0, *iter);
            break;
        }

        for (int i = 1; i < static_cast<int>(verticies.size()); ++i)
        {
            // Skip this iteration if next node is in previous nodes
            if (iter->find(i) != iter->end())
                continue;

            if (iter->empty()) // Null set
            {
                // Path to i from starting vertex (0)
                paths[{ i, * iter }] = edge_weights[i][0];
            }
            else
            {
                find_distance(paths, edge_weights, i, *iter);
            }
        }
    }

    return paths;
}


void Held_Karp_TSP::trace_path(Paths_container_t& paths, const Adjacency_matrix_t& edge_weights, Set_t final_path)
{
    int next_vertex = 0;
    for (int i = 0; i < static_cast<int>(verticies.size()) - 1; ++i)
    {

        int previous_vertex = find_distance(paths, edge_weights, next_vertex, final_path);
        edges.insert({ previous_vertex, next_vertex });
        final_path.erase(previous_vertex);
        next_vertex = previous_vertex;
    }
    edges.insert({ 0, next_vertex });
}


int Held_Karp_TSP::find_distance(Paths_container_t& paths, const Adjacency_matrix_t& edge_weights,
    int vertex_to, const Set_t& previous_verticies)
{
    double min_distance = numeric_limits<double>::infinity();
    Set_t previous_nodes{ previous_verticies };
    vector<int>  intermediates(previous_verticies.begin(), previous_verticies.end());
    int previous_vertex = numeric_limits<int>::lowest();
    for (auto intermediate : intermediates)
    {
        previous_nodes.erase(intermediate);
        double distance = edge_weights[vertex_to][intermediate] + paths[{intermediate, previous_nodes}];
        if (distance < min_distance)
        {
            min_distance = distance;
            previous_vertex = intermediate;
        }
        previous_nodes.insert(intermediate);
    }
    paths[{ vertex_to, previous_verticies }] = min_distance;
    return previous_vertex;
}
