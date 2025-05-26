#pragma once

#include <memory>

#include "AbstractFileLoaderCreator.h"
#include "FileLoaderTXT.h"

class FileLoaderTXTCreator : public AbstractFileLoaderCreator
{
public:
    ~FileLoaderTXTCreator() override = default;

    std::shared_ptr<AbstractFileLoader> create(const std::filesystem::path &path) override
    {
        return std::make_shared<FileLoaderTXT>(path);
    }
};