#ifndef HANDLER_HPP
#define HANDLER_HPP

#include "errors.hpp"
#include "renderer.hpp"
#include "transformGraph.hpp"
#include "graphics.hpp"
#include "app.hpp"

typedef enum command_t
{
    INIT,
    TRANSFORM,
    RENDER,
    DESTROY,
} command;

typedef struct request_t
{
    const char *pathToFile;
    graphics graphics;
    command command;
    transform transform;
} request;

errCode handler_sendRequestRender(const graphics &graphics);
errCode handler_sendRequestInit(const char *pathToFile);
errCode handler_sendRequestDestroy();
errCode handler_sendRequestTransform(const transform &transform);
errCode handler_handleRequest(const request &request);

#endif //HANDLER_HPP
