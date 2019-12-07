#include "MST.h"
#include <cmath>
#include <iostream>

using std::endl;

MST::MST(std::istream& is)
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

void MST::save(std::ostream& os) const
{
	os << verticies.size() << endl;
	for (const auto& pair : verticies)
		os << pair.second.x << " " << pair.second.y << " " << pair.second.z << endl;

	os << endl;

	os << total_edge_weight << endl;

	for (auto iter = edges.begin(); iter != edges.end(); ++iter)
		os << iter->first << " " << iter->second << endl;
}

double MST::cartesian_distance(const Vertex& v1, const Vertex& v2) const
{
	return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2) + pow(v2.z- v1.z, 2));
}
