#pragma once

#include <memory>

#include "AbstractFileLoaderCreator.h"
#include "FileLoaderCSV.h"

class FileLoaderCSVCreator : public AbstractFileLoaderCreator
{
public:
    ~FileLoaderCSVCreator() override = default;

    std::shared_ptr<AbstractFileLoader> create(const std::filesystem::path &path) override
    {
        return std::make_shared<FileLoaderCSV>(path);
    }
};