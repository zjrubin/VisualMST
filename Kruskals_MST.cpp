#include "Kruskals_MST.h"
#include <queue>
#include <numeric>
#include <utility>
#include <vector>

using std::iota;
using std::istream;
using std::priority_queue;
using std::vector;

using membership_containter_t = vector<int>;

static int find_set(const membership_containter_t& memberships, int vertex_index);
static void set_union(membership_containter_t& memberships, int vertex1, int vertex2);

struct Edge
{
	double distance;
	size_t vertex1_index;
	size_t vertex2_index;
};

Kruskals_MST::Kruskals_MST(istream& is)
	: MST{is}
{
	// Create a list of all possible edges
	using Edge_t = Edge;
	vector<Edge_t> all_edges;
	all_edges.reserve(verticies.size()*(verticies.size() - 1) / 2); // Enough capacity for number of edges of a fully connected graph
	for (size_t i = 0; i < verticies.size() - 1; ++i)
	{
		for (size_t j = i + 1; j < verticies.size(); ++j)
		{
			all_edges.push_back({ cartesian_distance(verticies[i], verticies[j]), i, j });
		}
	}

	// Apply Kruskal's Algorithm
	auto comp = [](const Edge_t& lhs, const Edge_t& rhs) {return lhs.distance > rhs.distance; }; // for min priority_queue
	using Edge_container_t = priority_queue<Edge_t, vector<Edge_t>, decltype(comp)>;
	Edge_container_t edge_queue(comp, move(all_edges)); // Priority queue of all edges

	vector<int> memberships(verticies.size());
	iota(memberships.begin(), memberships.end(), 0); // Mapping of vertex -> set it belongs to

	while (!edge_queue.empty())
	{
		Edge_t edge = edge_queue.top();
		edge_queue.pop();
		
		if (find_set(memberships, edge.vertex1_index) != find_set(memberships, edge.vertex2_index))
		{
			total_edge_weight += edge.distance;
			edges.insert({ edge.vertex1_index, edge.vertex2_index });
			set_union(memberships, edge.vertex1_index, edge.vertex2_index);
		}
	}
}

static int find_set(const membership_containter_t& memberships, int vertex_index)
{
	if (memberships[vertex_index] == vertex_index)
		return vertex_index;
	return find_set(memberships, memberships[vertex_index]);
}

static void set_union(membership_containter_t& memberships, int vertex1, int vertex2)
{
	int old_set = vertex1;
	while (memberships[old_set] != memberships[vertex2])
	{
		int tmp = memberships[old_set];
		memberships[old_set] = memberships[vertex2];
		old_set = tmp;
	}
}
