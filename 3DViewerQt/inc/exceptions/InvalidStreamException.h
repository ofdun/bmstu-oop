#pragma once

#include "BaseException.h"

class InvalidStreamException final : public BaseException
{
public:
    InvalidStreamException(const char *filename,
                           const char *funcName,
                           int line,
                           time_t time,
                           const char *text = "Stream is not valid!") :
        BaseException(
            filename, funcName, line, time, text)
    {
    }
};