#include "Graph.h"
#include <cmath>
#include <iostream>
#include <limits>

using std::endl;
using std::numeric_limits;
using std::vector;

Graph::Graph(std::istream& is)
	: total_edge_weight{ 0 }
{
	// Read in verticies
	int vertex_number = 0;
	double x, y, z;
	while (is >> x >> y >> z)
	{
		verticies[vertex_number++] = Vertex{ x,y,z };
	}
}

void Graph::save(std::ostream& os) const
{
	os << verticies.size() << endl;
	for (const auto& pair : verticies)
		os << pair.second.x << " " << pair.second.y << " " << pair.second.z << endl;

	os << endl;

	os << total_edge_weight << endl;

	for (auto iter = edges.begin(); iter != edges.end(); ++iter)
		os << iter->first << " " << iter->second << endl;
}

Graph::Adjacency_matrix_t Graph::create_adjacency_matrix()
{
	Adjacency_matrix_t edge_weights(verticies.size(), vector<double>(verticies.size(), numeric_limits<double>::infinity()));
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

	return edge_weights;
}

double Graph::cartesian_distance(const Vertex& v1, const Vertex& v2) const
{
	return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2) + pow(v2.z- v1.z, 2));
}
