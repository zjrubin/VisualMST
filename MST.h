#ifndef MST_H
#define MST_H

#include <iosfwd>

class MST
{
public:
	virtual ~MST()
	{}

	/*
	Outputs an MST in save-format:
	- number of vertices
	- coordinates for each vertex
	- \n
	- total_edge_weight of the MST
	- connections between vertices that form an MST
	*/
	virtual void save(std::ostream& os) const = 0;

	virtual double get_total_edge_weight() const = 0;

protected:
	struct Vertex
	{
		double x;
		double y;
		double z;
	};

	double cartesian_distance(const Vertex& v1, const Vertex& v2) const;
};

#endif // !MST_H
