#pragma once
#include "BaseException.h"

class FileDoesNotExistException final : public BaseException
{
public:
    FileDoesNotExistException(const char *filename,
                              const char *funcName,
                              int line,
                              time_t time,
                              const char *text = "File does not exist!") :
        BaseException(
            filename, funcName, line, time, text)
    {
    }
};

class FileIsADirectoryException final : public BaseException
{
public:
    FileIsADirectoryException(const char *filename,
                              const char *funcName,
                              int line,
                              time_t time,
                              const char *text = "File is a directory!") :
        BaseException(
            filename, funcName, line, time, text)
    {
    }
};

class FileIsNotOpeningException final : public BaseException
{
public:
    FileIsNotOpeningException(const char *filename,
                              const char *funcName,
                              int line,
                              time_t time,
                              const char *text = "Could not open a file!") :
        BaseException(
            filename, funcName, line, time, text)
    {
    }
};