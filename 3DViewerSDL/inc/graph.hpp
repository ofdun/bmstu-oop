#ifndef GRAPH_HPP__
#define GRAPH_HPP__

#include "errors.hpp"
#include "point.hpp"

#include <stdlib.h>

typedef struct
{
    size_t first;
    size_t second;
} edge;

typedef struct
{
    size_t pointsCount;
    size_t edgesCount;
    point *points;
    edge *edges;
} graph;

point graph_centerPoint(const graph &graph);

graph *graph_init(size_t points, size_t edges);
errCode graph_readFromFilename(graph *&gr, const char *filename);
errCode graph_readFromFile(graph *&gr, FILE *file);
void graph_free(graph *&gr);

#endif // GRAPH_HPP__
