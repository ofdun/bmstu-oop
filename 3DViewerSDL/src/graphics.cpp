#include "graphics.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

struct graphics_t
{
    SDL_Window *window;
    SDL_Renderer *renderer;
};

errCode graphics_drawPoints(const graphics &graphics, const point *points, size_t count)
{
    errCode rc = ERR_OK;

    if (!points)
        rc = ERR_NULL_POINTER;
    
    for (size_t i = 0; rc == ERR_OK && i < count; i++)
        rc = graphics_drawPoint(graphics, points[i]);

    return rc;
}

errCode graphics_drawPoint(const graphics &graphics, const point &point)
{
    errCode rc = ERR_OK;

    if (graphics == NULL)
        rc = ERR_NULL_POINTER;

    if (rc == ERR_OK && !SDL_RenderPoint(graphics->renderer, point.x, point.y))
        rc = ERR_COULDNT_DRAW_POINT;

    return rc;
}

errCode graphics_drawLine(const graphics &graphics, const point &p1, const point &p2)
{
    errCode rc = ERR_OK;

    if (graphics == NULL)
        rc = ERR_NULL_POINTER;

    if (rc == ERR_OK && !SDL_RenderLine(graphics->renderer, p1.x, p1.y, p2.x, p2.y))
        rc = ERR_COULDNT_DRAW_POINT;

    return rc;
}

void graphics_delay(unsigned int ms)
{
    SDL_Delay(ms);
}

void graphics_eventHandler(bool &ended)
{
    SDL_Event event;

    ended = false;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_EVENT_QUIT:
                ended = true;
                break;
            default:
                break;
        }
    }
}

errCode graphics_clearRenderer(const graphics &graphics)
{
    color color = graphics_colorInit(BACKGROUND_COLOR_R, BACKGROUND_COLOR_G, BACKGROUND_COLOR_B, BACKGROUND_COLOR_ALPHA);
    errCode rc = graphics_setRenderColor(graphics, color);

    if (rc == ERR_OK && !SDL_RenderClear(graphics->renderer))
        rc = ERR_COULDNT_CLEAR_RENDER;

    return rc;
}

errCode graphics_setRenderColor(const graphics &graphics, const color &color)
{
    errCode rc = ERR_OK;

    if (!SDL_SetRenderDrawColor(graphics->renderer, color.red, color.green, color.blue, color.alpha))
        rc = ERR_COULDNT_SET_RENDER_COLOR;

    return rc;
}

errCode graphics_update(const graphics &graphics)
{
    errCode rc = ERR_OK;

    if (!SDL_RenderPresent(graphics->renderer))
        rc = ERR_COULDNT_UPDATE_RENDER;

    return rc;
}

color graphics_colorInit(int red, int green, int blue, int alpha)
{
    color color;
    
    color.red = red;
    color.blue = blue;
    color.green = green;
    color.alpha = alpha;

    return color;
}

bool graphics_keyDown(const char *keyName)
{
    static const bool *keyboardState = SDL_GetKeyboardState(NULL);
    return keyboardState[SDL_GetScancodeFromName(keyName)];
}

errCode graphics_initGraphics(graphics &graphics)
{
    errCode rc = ERR_OK;

    if (rc == ERR_OK)
        graphics = (graphics_t *)malloc(sizeof(struct graphics_t));

    if (rc == ERR_OK && !graphics)
        rc = ERR_MEM_ALLOC;

    if (rc == ERR_OK && SDL_Init(SDL_INIT_VIDEO) != true)
        rc = ERR_COULDNT_INIT_GRAPHICS;

    if (rc == ERR_OK)
        graphics->window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    if (rc == ERR_OK && graphics->window == NULL)
        rc = ERR_COULDNT_INIT_GRAPHICS;

    if (rc == ERR_OK)
        graphics->renderer = SDL_CreateRenderer(graphics->window, NULL);
    
    if (rc == ERR_OK && graphics->renderer == NULL)
    {
        graphics_free(graphics);
        rc = ERR_COULDNT_INIT_GRAPHICS;
    }

    return rc;
}

void graphics_free(graphics &graphics)
{
    if (!graphics) { }
    else
    {
        SDL_DestroyRenderer(graphics->renderer);
        SDL_DestroyWindow(graphics->window);
    }
    free(graphics);
    graphics = NULL;
    SDL_Quit();
}
