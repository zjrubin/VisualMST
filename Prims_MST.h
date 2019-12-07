#ifndef PRIMS_MST_H
#define PRIMS_MST_H

#include "MST.h"
#include <map>

class Prims_MST final : public MST
{
public:
	Prims_MST(std::istream& is);
};

#endif // !PRIMS_MST_H
