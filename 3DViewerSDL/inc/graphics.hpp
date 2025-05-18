#ifndef GRAPHICS_HPP__
#define GRAPHICS_HPP__

#include "errors.hpp"
#include "point.hpp"

#include <stdlib.h>

typedef struct graphics_t *graphics;

typedef struct color_t
{
    int red;
    int green;
    int blue;
    int alpha;
} color;

color graphics_colorInit(int red, int green, int blue, int alpha);
errCode graphics_initGraphics(graphics &graphics);
bool graphics_keyDown(const char *keyName);
errCode graphics_setRenderColor(const graphics &graphics, const color &color);
errCode graphics_clearRenderer(const graphics &graphics);
errCode graphics_update(const graphics &graphics);
errCode graphics_drawPoint(const graphics &graphics, const point &point);
errCode graphics_drawPoints(const graphics &graphics, const point *points, size_t count);
errCode graphics_drawLine(const graphics &graphics, const point &p1, const point &p2);
void graphics_eventHandler(bool &ending);
void graphics_delay(unsigned int ms);
void graphics_free(graphics &graphics);

#endif // GRAPHICS_HPP__
