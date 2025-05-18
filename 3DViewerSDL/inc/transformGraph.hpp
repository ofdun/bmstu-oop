#ifndef TRANSFORMGRAPH_HPP__
#define TRANSFORMGRAPH_HPP__

#include "graph.hpp"
#include "transform.hpp"

void transformGraph_rotate(const graph &graph, const rotation &rotation);
void transformGraph_translate(const graph &graph, const offset &offset);
void transformGraph_scale(const graph &graph, const scale &scale);

#endif // !TRANSFORMGRAPH_HPP__
