#ifndef BASEEXCEPTION_H
#define BASEEXCEPTION_H

#include <exception>
#include <cstdio>
#include <ctime>

class BaseException : public std::exception
{
public:
    BaseException(const char *filename,
                  const char *funcName,
                  int line,
                  time_t time,
                  const char *text)
    {
        snprintf(errorText, maxErrorTextLen, format, filename, funcName, line, ctime(&time), text);
    }

    const char *what() const noexcept override
    {
        return errorText;
    }

    ~BaseException() override = default;
protected:
    static constexpr int maxErrorTextLen = 255;
    
    char errorText[maxErrorTextLen];
private:
    static constexpr auto format = "\nFilename: %s\nFunction: %s\nLine: %d\nTime: %s\nError: %s";
};

#endif //BASEEXCEPTION_H