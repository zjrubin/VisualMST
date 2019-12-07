#ifndef KRUSKALS_MST_H
#define KRUSKALS_MST_H

#include "MST.h"
#include <map>

class Kruskals_MST final : public MST
{
public:
	Kruskals_MST(std::istream& is);
};

#endif // !KRUSKALS_MST_H
