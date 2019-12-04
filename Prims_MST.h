#ifndef PRIMS_MST_H
#define PRIMS_MST_H

#include "MST.h"
#include <map>

class Prims_MST : public MST
{
public:
	Prims_MST(std::istream& is);

	void save(std::ostream& os) const override;

	double get_total_edge_weight() const override
	{ return total_edge_weight; }

private:
	double total_edge_weight;

	using vertex_container_t = std::map<int, Vertex>;
	vertex_container_t verticies;

	using edge_container_t = std::multimap<int, int>;
	edge_container_t edges;
};

#endif // !PRIMS_MST_H
