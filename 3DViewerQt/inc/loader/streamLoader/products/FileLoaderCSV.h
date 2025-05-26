#pragma once
#include "AbstractFileLoader.h"

class FileLoaderCSV : public AbstractFileLoader
{
public:
    ~FileLoaderCSV() override = default;

    explicit FileLoaderCSV(const std::filesystem::path &path);

    void open() override;
    void close() override;
    std::shared_ptr<std::ifstream> get() override;
};