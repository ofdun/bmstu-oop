#include "graph.hpp"


static errCode graph_inputEdgeFromFile(FILE *f, edge &edge);
static errCode graph_inputEdgesFromFile(FILE *f, edge *edges, size_t count);

graph *graph_init(size_t points, size_t edges)
{
    graph *gr = (graph *) malloc(sizeof(graph));

    if (gr)
    {
        gr->edgesCount = edges;
        gr->pointsCount = points;
        gr->points = (point *) malloc(sizeof(point) * points);
        gr->edges = (edge *) malloc(sizeof(edge) * edges);
    }

    if (gr && (!gr->points || !gr->edges))
        graph_free(gr);

    return gr;
}

point graph_centerPoint(const graph &graph)
{
    point p = point_addPoints(graph.points, graph.pointsCount);

    if (graph.pointsCount > 0)
        point_multiply(p, 1. / graph.pointsCount);

    return p;
}

void graph_free(graph *&gr)
{
    if (gr)
    {
        free(gr->points);
        free(gr->edges);
    }
    free(gr);

    gr = NULL;
}

errCode graph_readFromFilename(graph *&gr, const char *filename)
{
    errCode rc = ERR_OK;

    if (rc == ERR_OK && filename == NULL)
        rc = ERR_NULL_POINTER;

    FILE *f = NULL;
    if (rc == ERR_OK)
        f = fopen(filename, "r");

    if (rc == ERR_OK && !f)
        rc = ERR_WRONG_FILE;

    if (rc == ERR_OK)
        rc = graph_readFromFile(gr, f);

    if (f)
        fclose(f);

    return rc;
}

static errCode graph_inputEdgesFromFile(FILE *f, edge *edges, size_t count)
{
    errCode rc = ERR_OK;
    
    for (size_t i = 0; rc == ERR_OK && i < count; i++)
        rc = graph_inputEdgeFromFile(f, edges[i]);

    return rc;
}

static errCode graph_inputEdgeFromFile(FILE *f, edge &edge)
{
    errCode rc = ERR_OK;
    
    if (rc == ERR_OK && !f)
        rc = ERR_WRONG_FILE;

    if (rc == ERR_OK && fscanf(f, "%zu%zu", &edge.first, &edge.second) != 2)
        rc = ERR_WRONG_FILE_STRUCTURE;

    return rc;
}

errCode graph_readFromFile(graph *&gr, FILE *file)
{
    errCode rc = ERR_OK;

    if (rc == ERR_OK && file == NULL)
        rc = ERR_NULL_POINTER;

    size_t pointsCount = 0, edgesCount = 0;
    if (rc == ERR_OK && fscanf(file, "%zu%zu", &pointsCount, &edgesCount) != 2)
        rc = ERR_WRONG_FILE_STRUCTURE;

    if (rc == ERR_OK)
        gr = graph_init(pointsCount, edgesCount);

    if (rc == ERR_OK && !gr)
        rc = ERR_MEM_ALLOC;

    if (rc == ERR_OK)
        rc = point_inputPoints(file, gr->points, gr->pointsCount);

    if (rc == ERR_OK)
        rc = graph_inputEdgesFromFile(file, gr->edges, gr->edgesCount);

    if (rc != ERR_OK)
        graph_free(gr);

    return rc;
}
