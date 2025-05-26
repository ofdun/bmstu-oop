#pragma once

#include "BaseException.h"

class SceneManagerNotSetException final : public BaseException
{
public:
    SceneManagerNotSetException(const char *filename,
                                const char *funcName,
                                int line,
                                time_t time,
                                const char *text = "Scene manager is not set!") :
        BaseException(
            filename, funcName, line, time, text)
    {
    }
};

class AbstractFactoryNotSetException final : public BaseException
{
public:
    AbstractFactoryNotSetException(const char *filename,
                                   const char *funcName,
                                   int line,
                                   time_t time,
                                   const char *text = "Abstract factory is not set!") :
        BaseException(
            filename, funcName, line, time, text)
    {
    }
};

class NoCameraSetException final : public BaseException
{
public:
    NoCameraSetException(const char *filename,
                         const char *funcName,
                         int line,
                         time_t time,
                         const char *text = "Camera is not set!") :
        BaseException(
            filename, funcName, line, time, text)
    {
    }
};
