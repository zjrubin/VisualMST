#ifndef MST_H

#include <iosfwd>
#include <map>

class MST
{
public:
	MST(std::istream& is);

	/*
	Outputs an MST in save-format:
	- number of vertices
	- coordinates for each vertex
	- \n
	- total_edge_weight of the MST
	- connections between vertices that form an MST
	*/
	void save(std::ostream& os);

	double get_total_edge_weight() const
	{ return total_edge_weight; }

private:
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

#endif // !MST_H
