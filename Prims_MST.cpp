#include "Prims_MST.h"
#include <istream>
#include <limits>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using std::endl;
using std::istream; using std::ostream;
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
	: MST{}, total_edge_weight { 0 }
{
	// Read in verticies
	int vertex_number = 0;
	double x, y, z;
	while (is >> x >> y >> z)
	{
		verticies[vertex_number++] = Vertex{ x,y,z };
	}

	// Create edge weight adjacency matrix
	vector<vector<double>> edge_weights(verticies.size(), vector<double>(verticies.size(), numeric_limits<double>::infinity()));
	for (size_t i = 0; i < verticies.size(); ++i)
	{
		for (size_t j = 0; j < verticies.size(); ++j)
		{
			// Disallow self-edges
			if (i == j)
				continue;

			edge_weights[i][j] = cartesian_distance(verticies[i], verticies[j]);
		}
	}

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

void Prims_MST::save(ostream& os) const
{
	os << verticies.size() << endl;
	for (const auto& pair : verticies)
		os << pair.second.x << " " << pair.second.y << " " << pair.second.z << endl;

	os << endl;

	os << total_edge_weight << endl;

	for (auto iter = edges.begin(); iter != edges.end(); ++iter)
		os << iter->first << " " << iter->second << endl;
}
