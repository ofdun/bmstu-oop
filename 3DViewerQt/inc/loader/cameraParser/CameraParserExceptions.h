#pragma once

#include "BaseException.h"

class InvalidCameraDirectionException final : public BaseException
{
public:
    InvalidCameraDirectionException(const char *filename,
                                    const char *funcName,
                                    int line,
                                    time_t time,
                                    const char *text = "Camera direction format is invalid!") :
        BaseException(
            filename, funcName, line, time, text)
    {
    }
};

class InvalidCameraPositionException final : public BaseException
{
public:
    InvalidCameraPositionException(const char *filename,
                                   const char *funcName,
                                   int line,
                                   time_t time,
                                   const char *text = "Camera position format is invalid!") :
        BaseException(
            filename, funcName, line, time, text)
    {
    }
};