#ifndef KRUSKALS_MST_H
#define KRUSKALS_MST_H

#include "Graph.h"

class Kruskals_MST final : public Graph
{
public:
	Kruskals_MST(std::istream& is);
};

#endif // !KRUSKALS_MST_H
