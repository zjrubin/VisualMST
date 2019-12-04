#include "MST.h"
#include <cmath>
#include <limits>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using std::istream;
using std::map;
using std::numeric_limits;
using std::pair;
//using std::priority_queue;
using std::vector;

MST::MST(istream& is)
	: total_edge_weight{ 0 }
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


	map<int, pair<double, int>> costs; // Map from: vertex number -> {cost, previous vertex}s
	for (size_t i = 0; i < verticies.size(); ++i)
		costs[i] = pair{ std::numeric_limits<double>::infinity(), std::numeric_limits<int>::lowest() };

	costs[0] = { 0, std::numeric_limits<int>::lowest() }; // Starting vertex has no cost and no previous vertex
	
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
				if (edge_weight < iter->second.first)
				{
					iter->second.first = edge_weight; // set cost
					iter->second.second = min_cost_vertex_num; // set previous
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
}

double MST::cartesian_distance(const Vertex& v1, const Vertex& v2) const
{
	return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2) + pow(v2.z- v1.z, 2));
}


