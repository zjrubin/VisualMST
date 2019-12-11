#include "Prims_MST.h"
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using std::istream;
using std::map;
using std::numeric_limits;
using std::pair;
using std::vector;

constexpr int invalid_node_number_c = numeric_limits<int>::lowest();

struct Vertex_Attributes
{
	double cost;
	int previous;
};

Prims_MST::Prims_MST(istream& is)
	: Graph{is}
{
	Adjacency_matrix_t edge_weights = create_adjacency_matrix();

	map<int, Vertex_Attributes> costs; // Map from: vertex number -> {cost, previous vertex}s
	for (size_t i = 0; i < verticies.size(); ++i)
		costs[i] = { std::numeric_limits<double>::infinity(), invalid_node_number_c };

	costs[0] = { 0, invalid_node_number_c }; // Starting vertex has no cost and no previous vertex

	int min_cost_vertex_num = 0; // Vertex 0 is the starting vertex
	while (!costs.empty())
	{
		auto [cost, previous] = costs[min_cost_vertex_num];
		costs.erase(min_cost_vertex_num);

		total_edge_weight += cost;
		edges.insert({ previous, min_cost_vertex_num });

		double min_edge_weight = numeric_limits<double>::infinity();
		int next_min_cost_vertex_num = numeric_limits<int>::lowest();
		for (size_t i = 0; i < edge_weights[min_cost_vertex_num].size(); ++i)
		{
			auto iter = costs.find(i);
			if (iter != costs.end())
			{
				double edge_weight = edge_weights[min_cost_vertex_num][i];
				if (edge_weight < iter->second.cost)
				{
					iter->second.cost = edge_weight;
					iter->second.previous = min_cost_vertex_num;
				}

				if (edge_weight < min_edge_weight)
				{
					min_edge_weight = edge_weight;
					next_min_cost_vertex_num = i;
				}
			}
		}

		min_cost_vertex_num = next_min_cost_vertex_num;
	}

	// Remove the invalid starting node
	edges.erase(invalid_node_number_c);
}
