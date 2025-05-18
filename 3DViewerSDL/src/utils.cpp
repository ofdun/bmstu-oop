#include "utils.hpp"

void utils_printError(errCode rc)
{
    switch (rc)
    {
        case ERR_NOT_INIT:
            printf("Ошибка! Сначала необходимо инициализировать данные!\n");
        case ERR_WRONG_ARGS:
            printf("Ошибка! Неправильные аргументы программы!\n");
        break;
        case ERR_WRONG_FILE:
            printf("Ошибка! Не удалось открыть файл!\n");
        break;
        case ERR_NULL_POINTER:
            printf("Ошибка! Нулевой указатель!\n");
        break;
        case ERR_WRONG_FILE_STRUCTURE:
            printf("Ошибка! Неправильная структура файла!\n");
        break;
        case ERR_COULDNT_INIT_GRAPHICS:
            printf("Ошибка! Не удалось инициализовать графический интерфейс!\n");
        break;
        case ERR_COULDNT_DRAW_POINT:
            printf("Ошибка! Не удалось отрисовать точку!\n");
        break;
        case ERR_COULDNT_DRAW_LINE:
            printf("Ошибка! Не удалось отрисовать прямую!\n");
        break;
        case ERR_COULDNT_UPDATE_RENDER:
            printf("Ошибка! Не удалось обновить изображение!\n");
        break;
        case ERR_COULDNT_SET_RENDER_COLOR:
            printf("Ошибка! Не удалось установить цвет рендера!\n");
        break;
        case ERR_COULDNT_CLEAR_RENDER:
            printf("Ошибка! Не удалось очистить изображение!\n");
        break;
        case ERR_MEM_ALLOC:
            printf("Ошибка! Не удалось выделить память!\n");
        break;

        default:
            break;
    }
}

transform utils_loadTransformInitPos()
{
    return transform_init(transform_scaleInit(SCALE_X, SCALE_Y, SCALE_Z),
        transform_rotationInit(ROTATION_X, ROTATION_Y, ROTATION_Z),
        transform_offsetInit(OFFSET_X, OFFSET_Y, OFFSET_Z));
}

offset utils_parseOffsetFromKeyPresses(bool &changed)
{
    double offsetX = 0;
    double offsetY = 0;
    double offsetZ = 0;
    if (graphics_keyDown("A"))
        offsetX -= OFFSET_STEP;
    if (graphics_keyDown("D"))
        offsetX += OFFSET_STEP;
    if (graphics_keyDown("W"))
        offsetY -= OFFSET_STEP;
    if (graphics_keyDown("S"))
        offsetY += OFFSET_STEP;

    changed = offsetX != 0 || offsetY != 0 || offsetZ != 0;

    return transform_offsetInit(offsetX, offsetY, offsetZ);
}

rotation utils_parseRotationFromKeyPresses(bool &changed)
{
    double degreeX = 0;
    double degreeY = 0;
    double degreeZ = 0;
    if (graphics_keyDown("T"))
        degreeX -= ROTATION_STEP;
    if (graphics_keyDown("Y"))
        degreeX += ROTATION_STEP;
    if (graphics_keyDown("G"))
        degreeY += ROTATION_STEP;
    if (graphics_keyDown("H"))
        degreeY -= ROTATION_STEP;
    if (graphics_keyDown("V"))
        degreeZ -= ROTATION_STEP;
    if (graphics_keyDown("B"))
        degreeZ += ROTATION_STEP;

    changed = degreeX != 0 || degreeY != 0 || degreeZ != 0;

    return transform_rotationInit(degreeX, degreeY, degreeZ);
}

scale utils_parseScaleFromKeyPresses(bool &changed)
{
    double totalScale = 1;
    if (graphics_keyDown("E"))
        totalScale *= SCALE_STEP;
    if (graphics_keyDown("Q"))
        totalScale *= 1 / SCALE_STEP;

    changed = totalScale != 1;

    return transform_scaleInit(totalScale, totalScale, totalScale);
}

transform utils_parseTransformFromKeyPresses(bool &changed)
{
    bool scaleChanged = false;
    bool rotationChanged = false;
    bool offsetChanged = false;
    const transform transform = transform_init(
        utils_parseScaleFromKeyPresses(scaleChanged),
        utils_parseRotationFromKeyPresses(rotationChanged),
        utils_parseOffsetFromKeyPresses(offsetChanged)
    );

    changed = scaleChanged || rotationChanged || offsetChanged;

    return transform;
}
