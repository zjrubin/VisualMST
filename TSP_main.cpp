// #include <cassert>
// #include <iostream>
// #include <limits>
// #include <map>
// #include <numeric>
// #include <set>
// #include <vector>

// using namespace std;

// using Set_t = set<int>;
// template<typename T>
// struct Set_Comp
// {
//     using is_transparent = std::true_type;
//     bool operator() (const set<T>& lhs, const set<T>& rhs) const
//     {
//         if (lhs.size() != rhs.size())
//             return lhs.size() < rhs.size();

//         for (auto iter1 = lhs.begin(), iter2 = rhs.begin(); iter1 != lhs.end(); ++iter1, ++iter2)
//         {
//             if (*iter1 != *iter2)
//                 return *iter1 < *iter2;
//         }

//         assert(!"This point shold not be reached");
//         return false;
//     }
// };
// using Power_Set_t = set<Set_t, Set_Comp<int>>;

// struct Path
// {
//     int vertex_to;
//     Set_t previous_vertices;
// };

// struct Comp_Path
// {
//     using is_transparent = std::true_type;
//     bool operator() (const Path& lhs, const Path& rhs) const
//     {
//         if (lhs.previous_vertices.size() != rhs.previous_vertices.size())
//             return lhs.previous_vertices.size() < rhs.previous_vertices.size();

//         if (lhs.vertex_to != rhs.vertex_to)
//             return lhs.vertex_to < rhs.vertex_to;

//         auto& lprev = lhs.previous_vertices;
//         auto& rprev = rhs.previous_vertices;
//         for (auto iter1 = lprev.begin(), iter2 = rprev.begin(); iter1 != lprev.end(); ++iter1, ++iter2)
//         {
//             if (*iter1 != *iter2)
//                 return *iter1 < *iter2;
//         }

//         //assert(!"This point shold not be reached");
//         return false; // lhs !< rhs
//     }
// };

// using Paths_container_t = map<Path, double, Comp_Path>;

// constexpr int num_edges_c = 4;

// Power_Set_t generate_power_set(int n);
// void find_distance(Paths_container_t& paths, double edge_weights[][num_edges_c], int vertex_to, const Set_t& previous_verticies);
// ostream& operator << (ostream& os, const Power_Set_t& powerset);

// int main()
// {
//     // Edge weights from https://www.youtube.com/watch?v=-JjA4BLQyqE
//     double edge_weights[][num_edges_c] = {
//         { 0,  2,  9, 10},
//         { 1,  0,  6,  4},
//         {15,  7,  0,  8},
//         { 6,  3, 12,  0}
//     };

//     Paths_container_t paths;

//     Power_Set_t powerset = generate_power_set(num_edges_c - 1);

//     // Iterate from the null set through every subset, but exclude the full set itself
//     for (auto iter = powerset.begin(); iter != powerset.end(); ++iter)
//     {
//         // calculate distance back to starting vertex
//         if (iter->size() == num_edges_c - 1)
//         {
//             find_distance(paths, edge_weights, 0, *iter);
//             break;
//         }

//         for (int i = 1; i < num_edges_c; ++i)
//         {
//             // Skip this iteration if next node is in previous nodes
//             if (iter->find(i) != iter->end())
//                 continue;

//             if (iter->empty()) // Null set
//             {
//                 // Path to i from starting vertex (0)
//                 paths[{ i, *iter }] = edge_weights[i][0];
//             }
//             else
//             {
//                 find_distance(paths, edge_weights, i, *iter);
//             }
//         }
//     }

//     cout << "TSP distance: " << paths[{0, *powerset.rbegin()}] << endl;
//     cout << "Power set:\n" << powerset;

//     return 0;
// }

// Power_Set_t generate_power_set(int n)
// {
//     Power_Set_t powerset;
//     vector<int> stack(n + 1, 0);
//     int k = 0;

//     while (true)
//     {
//         if (stack[k] < n)
//         {
//             stack[k + 1] = stack[k] + 1;
//             k++;
//         }
//         else
//         {
//             stack[k - 1]++;
//             k--;
//         }

//         if (k == 0)
//             break;

//         powerset.emplace(stack.begin() + 1, stack.begin() + k + 1);
//         Set_t tmp(stack.begin() + 1, stack.begin() + k + 1);
//     }

//     // Add the null set
//     powerset.emplace();

//     return powerset;
// }

// void find_distance(Paths_container_t& paths, double edge_weights[][num_edges_c], int vertex_to, const Set_t& previous_verticies)
// {
//     double min_distance = numeric_limits<double>::infinity();
//     Set_t previous_nodes{ previous_verticies };
//     vector<int>  intermediates(previous_verticies.begin(), previous_verticies.end());
//     for (auto intermediate : intermediates)
//     {
//         previous_nodes.erase(intermediate);
//         double distance = edge_weights[vertex_to][intermediate] + paths[{intermediate, previous_nodes}];
//         if (distance < min_distance)
//         {
//             min_distance = distance;
//         }
//         previous_nodes.insert(intermediate);
//     }
//     paths[{ vertex_to, previous_verticies }] = min_distance;
// }

// ostream& operator << (ostream& os, const Power_Set_t& powerset)
// {
//     os << "null" << endl;
//     for (auto iter1 = ++powerset.begin(); iter1 != powerset.end(); ++iter1)
//     {
//         for (auto iter2 = iter1->begin(); iter2 != iter1->end(); ++iter2)
//             os << *iter2 << " ";
//         os << endl;
//     }
//     return os;
// }