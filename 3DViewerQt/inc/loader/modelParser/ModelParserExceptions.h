#pragma once

#include "BaseException.h"

class InvalidEdgeFromStreamException final : public BaseException
{
public:
    InvalidEdgeFromStreamException(const char *filename,
                                   const char *funcName,
                                   int line,
                                   time_t time,
                                   const char *text = "Model edge format is invalid!") :
        BaseException(
            filename, funcName, line, time, text)
    {
    }
};

class InvalidPointFromStreamException final : public BaseException
{
public:
    InvalidPointFromStreamException(const char *filename,
                                    const char *funcName,
                                    int line,
                                    time_t time,
                                    const char *text = "Model point format is invalid!") :
        BaseException(
            filename, funcName, line, time, text)
    {
    }
};