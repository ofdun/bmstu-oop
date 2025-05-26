#pragma once

#include <filesystem>

#include "AbstractFileLoader.h"

class FileLoaderTXT : public AbstractFileLoader
{
public:
    ~FileLoaderTXT() override = default;

    explicit FileLoaderTXT(const std::filesystem::path &path);

    void open() override;
    void close() override;
    std::shared_ptr<std::ifstream> get() override;
};