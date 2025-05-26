#pragma once

enum objType
{
    MODEL,
    CAMERA,
    NONE
};

enum managerType
{
    LOAD,
    RENDER,
    SCENE_ELEMENTS,
    SCENE,
    SELECT,
    TRANSFORM
};

enum modelImplementation
{
    MATRIX,
    EDGELIST
};
