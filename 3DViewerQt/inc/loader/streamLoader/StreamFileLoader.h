#pragma once

#include "AbstractFileLoader.h"

#include <filesystem>
#include <memory>

#include "AbstractStreamLoader.h"

class StreamFileLoader : public AbstractStreamLoader
{
public:
    ~StreamFileLoader() override = default;

    explicit StreamFileLoader(std::shared_ptr<AbstractFileLoader> fileLoader);

    std::shared_ptr<std::istream> getStream() override;
    void closeStream() override;

private:
    std::shared_ptr<AbstractFileLoader> fileLoader;
};