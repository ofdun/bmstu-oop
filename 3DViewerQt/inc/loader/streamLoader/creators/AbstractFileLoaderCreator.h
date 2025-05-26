#pragma once

#include <memory>
#include <filesystem>

#include "AbstractFileLoader.h"

class AbstractFileLoaderCreator
{
public:
    virtual ~AbstractFileLoaderCreator() = 0;

    virtual std::shared_ptr<AbstractFileLoader> create(const std::filesystem::path &path) = 0;
};