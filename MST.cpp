#include "MST.h"
#include <cmath>

double MST::cartesian_distance(const Vertex& v1, const Vertex& v2) const
{
	return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2) + pow(v2.z- v1.z, 2));
}
