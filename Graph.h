#ifndef GRAPH_H
#define GRAPH_H

#include <iosfwd>
#include <map>

class Graph
{
public:
	virtual ~Graph()
	{}

	/*
	Outputs an Graph in save-format:
	- number of vertices
	- coordinates for each vertex
	- \n
	- total_edge_weight of the Graph
	- connections between vertices that form an Graph
	*/
	void save(std::ostream& os) const;

protected:
	Graph(std::istream& is);

	struct Vertex
	{
		double x;
		double y;
		double z;
	};

	double total_edge_weight;

	using vertex_container_t = std::map<int, Vertex>;
	vertex_container_t verticies;

	using edge_container_t = std::multimap<int, int>;
	edge_container_t edges;

	double cartesian_distance(const Vertex& v1, const Vertex& v2) const;
};

#endif // !GRAPH_H
