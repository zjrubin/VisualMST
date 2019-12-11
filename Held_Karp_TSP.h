#ifndef HELD_KARP_TSP_H
#define HELD_KARP_TSP_H

#include "Graph.h"

class Held_Karp_TSP final : public Graph
{
public:
	Held_Karp_TSP(std::istream& is);
};

#endif // !HELD_KARP_TSP_H
