#include "handler.hpp"

static errCode handler_handleTransform(graph *&graph, const transform &transform)
{
    if (!graph)
        return ERR_NOT_INIT;

    transformGraph_translate(*graph, transform.offset);
    transformGraph_scale(*graph, transform.scale);
    transformGraph_rotate(*graph, transform.rotation);

    return ERR_OK;
}

errCode handler_sendRequestTransform(const transform &transform)
{
    request request;

    request.command = TRANSFORM;
    request.transform = transform;

    return handler_handleRequest(request);
}

static errCode handler_handleInit(graph *&graph, const char *pathToFile)
{
    errCode rc = ERR_OK;
    
    if (!pathToFile)
        rc = ERR_WRONG_FILE;

    if (rc == ERR_OK)
        rc = graph_readFromFilename(graph, pathToFile);

    if (rc == ERR_OK)
    {
        const transform initialPos = utils_loadTransformInitPos();
        rc = handler_sendRequestTransform(initialPos);
    }

    return rc;
}

errCode handler_sendRequestInit(const char *pathToFile)
{
    request request;
    request.command = INIT;
    request.pathToFile = pathToFile;
    return handler_handleRequest(request);
}

static errCode handler_handleRender(const graphics &graphics, graph *&graph)
{
    if (!graphics || !graph)
        return ERR_NOT_INIT;
    
    return renderer_renderGraph(graphics, *graph);
}

static errCode handler_handleDestroy(graph *&graph)
{
    if (!graph)
        return ERR_NOT_INIT;

    graph_free(graph);

    return ERR_OK;
}

errCode handler_sendRequestRender(const graphics &graphics)
{
    request request;
    request.graphics = graphics;
    request.command = RENDER;
    return handler_handleRequest(request);
}

errCode handler_sendRequestDestroy()
{
    request request;
    request.command = DESTROY;
    return handler_handleRequest(request);
}

errCode handler_handleRequest(const request &request)
{
    errCode rc = ERR_OK;

    static graph *graph = NULL;

    switch (request.command)
    {
        case INIT:
            rc = handler_handleInit( graph, request.pathToFile);
            break;
        case TRANSFORM:
            rc = handler_handleTransform(graph, request.transform);
            break;
        case RENDER:
            rc = handler_handleRender(request.graphics, graph);
            break;
        case DESTROY:
            rc = handler_handleDestroy(graph);
            break;
        default:
            break;
    }

    return rc;
}
