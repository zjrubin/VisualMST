#ifndef KRUSKALS_MST_H
#define KRUSKALS_MST_H

#include "MST.h"
#include <map>

class Kruskals_MST : public MST
{
public:
	Kruskals_MST(std::istream& is);

	void save(std::ostream& os) const override;

	double get_total_edge_weight() const override
	{ return total_edge_weight; }

private:
	double total_edge_weight;

	using vertex_container_t = std::map<int, Vertex>;
	vertex_container_t verticies;

	using edge_container_t = std::multimap<int, int>;
	edge_container_t edges;

	struct Edge;
};

#endif // !KRUSKALS_MST_H
