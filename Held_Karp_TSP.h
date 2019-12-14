#ifndef HELD_KARP_TSP_H
#define HELD_KARP_TSP_H

#include "Graph.h"
#include <set>

class Held_Karp_TSP final : public Graph
{
public:
	Held_Karp_TSP(std::istream& is);

private:
    using Set_t = std::set<int>;
    template<typename T>
    struct Set_Comp
    {
        using is_transparent = std::true_type;
        bool operator() (const std::set<T>& lhs, const std::set<T>& rhs) const;
    };
    using Power_Set_t = std::set<Set_t, Set_Comp<int>>;

    struct Path
    {
        int vertex_to;
        Set_t previous_vertices;
    };
    struct Comp_Path
    {
        using is_transparent = std::true_type;
        bool operator() (const Path& lhs, const Path& rhs) const;
    };
    using Paths_container_t = std::map<Path, double, Comp_Path>;

    Power_Set_t generate_power_set(int n);
    Paths_container_t generate_paths(const Adjacency_matrix_t& edge_weights, const Power_Set_t& powerset);
    void trace_path(Paths_container_t& paths, const Adjacency_matrix_t& edge_weights, Set_t final_path);
    int find_distance(Paths_container_t& paths, const Adjacency_matrix_t& edge_weights, int vertex_to, const Set_t& previous_verticies);
};

#endif // !HELD_KARP_TSP_H
