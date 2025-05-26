#pragma once
#include "BaseException.h"

class NotImplementedException final : public BaseException
{
public:
    NotImplementedException(const char *filename,
                            const char *funcName,
                            int line,
                            time_t time,
                            const char *text = "Method not implemented!") :
        BaseException(
            filename, funcName, line, time, text)
    {
    }
};