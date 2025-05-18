#include "transformGraph.hpp"

void transformGraph_rotate(const graph &graph, const rotation &rotation)
{
    point center = graph_centerPoint(graph);
    offset toStart = transform_offsetInit(-center.x, -center.y, -center.z);
    offset toResult = transform_offsetInit(center.x, center.y, center.z);
    transformGraph_translate(graph, toStart);
    
    point_rotatePoints(graph.points, graph.pointsCount, rotation);

    transformGraph_translate(graph, toResult);
}

void transformGraph_translate(const graph &graph, const offset &offset)
{
    point_translatePoints(graph.points, graph.pointsCount, offset);
}

void transformGraph_scale(const graph &graph, const scale &scale)
{
    point center = graph_centerPoint(graph);
    offset toStart = transform_offsetInit(-center.x, -center.y, -center.z);
    offset toResult = transform_offsetInit(center.x, center.y, center.z);
    transformGraph_translate(graph, toStart);
    
    point_scalePoints(graph.points, graph.pointsCount, scale);

    transformGraph_translate(graph, toResult);
}

