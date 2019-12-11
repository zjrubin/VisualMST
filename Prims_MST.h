#ifndef PRIMS_MST_H
#define PRIMS_MST_H

#include "Graph.h"

class Prims_MST final : public Graph
{
public:
	Prims_MST(std::istream& is);
};

#endif // !PRIMS_MST_H
