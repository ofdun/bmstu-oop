#ifndef MATRIXEXCEPTIONS_H
#define MATRIXEXCEPTIONS_H

#include "BaseException.h"

class InvalidInitSizeException final : public BaseException
{
public:
    InvalidInitSizeException(const char *filename,
                         const char *funcName,
                         int line,
                         time_t time,
                         const char *text = "Could not create mathematical matrix with given rows and columns!") : BaseException(filename, funcName, line, time, text) {}
};

class IncompatibleSizeException final : public BaseException
{
public:
    IncompatibleSizeException(const char *filename,
                         const char *funcName,
                         int line,
                         time_t time,
                         const char *text = "Operation with such dimensions is not possible!") : BaseException(filename, funcName, line, time, text) {}
};

class NotInvertibleException final : public BaseException
{
public:
    NotInvertibleException(const char *filename,
                         const char *funcName,
                         int line,
                         time_t time,
                         const char *text = "Matrix is not invertible!") : BaseException(filename, funcName, line, time, text) {}
};

class InvalidRowIndexException final : public BaseException
{
public:
    InvalidRowIndexException(const char *filename,
                         const char *funcName,
                         int line,
                         time_t time,
                         const char *text = "Invalid row index!") : BaseException(filename, funcName, line, time, text) {}
};

class InvalidColumnIndexException final : public BaseException
{
public:
    InvalidColumnIndexException(const char *filename,
                         const char *funcName,
                         int line,
                         time_t time,
                         const char *text = "Invalid column index!") : BaseException(filename, funcName, line, time, text) {}
};

class MemoryAllocationException final : public BaseException
{
public:
    MemoryAllocationException(const char *filename,
                         const char *funcName,
                         int line,
                         time_t time,
                         const char *text = "Could not allocate enough memory for a matrix!") : BaseException(filename, funcName, line, time, text) {}
};

class InvalidInitializerListException final : public BaseException
{
public:
    InvalidInitializerListException(const char *filename,
                         const char *funcName,
                         int line,
                         time_t time,
                         const char *text = "Invalid initializer list for a matrix!") : BaseException(filename, funcName, line, time, text) {}
};

#endif //MATRIXEXCEPTIONS_H
