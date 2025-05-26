#pragma once

#include <fstream>
#include <filesystem>
#include <memory>

class AbstractFileLoader
{
public:
    virtual ~AbstractFileLoader() = 0;

    virtual void open() = 0;
    virtual void close() = 0;
    virtual std::shared_ptr<std::ifstream> get() = 0;

protected:
    std::filesystem::path path;
    std::shared_ptr<std::ifstream> file;
};
