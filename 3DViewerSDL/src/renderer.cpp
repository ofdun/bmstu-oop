#include "renderer.hpp"

static errCode drawEdges(const graphics &graphics, const point *points, const edge *edges, size_t count)
{
    errCode rc = ERR_OK;
    
    for (size_t i = 0; rc == ERR_OK && i < count; i++)
    {
        const edge &edge = edges[i];
        size_t point1Index = edge.first;
        size_t point2Index = edge.second;
        rc = graphics_drawLine(graphics, points[point1Index], points[point2Index]);
    }

    return rc;
}

static errCode drawGraph(const graphics &graphics, const graph &graph)
{
    errCode rc = graphics_drawPoints(graphics, graph.points, graph.pointsCount);
    
    if (rc == ERR_OK)
        rc = drawEdges(graphics, graph.points, graph.edges, graph.edgesCount);

    return rc;
}

errCode renderer_renderGraph(const graphics &graphics, const graph &graph)
{
    errCode rc = graphics_clearRenderer(graphics);

    if (rc == ERR_OK)
    {
        const color color = graphics_colorInit(GRAPH_COLOR_R, GRAPH_COLOR_G, GRAPH_COLOR_B, GRAPH_COLOR_ALPHA);
        rc = graphics_setRenderColor(graphics, color);
    }

    if (rc == ERR_OK)
        rc = drawGraph(graphics, graph);

    if (rc == ERR_OK)
        rc = graphics_update(graphics);

    return rc;
}
