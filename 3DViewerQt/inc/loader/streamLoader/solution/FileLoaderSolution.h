#pragma once

#include <memory>
#include <filesystem>
#include <unordered_map>

#include "AbstractFileLoaderCreator.h"

class FileLoaderSolution
{
    using CreateCreator = std::shared_ptr<AbstractFileLoaderCreator> (*)();
    using CallbackMap = std::unordered_map<std::string, CreateCreator>;

public:
    FileLoaderSolution() = default;
    FileLoaderSolution(std::initializer_list<std::pair<std::string, CreateCreator>> list);

    bool registrate(std::string id, CreateCreator creationFunc);
    bool remove(std::string id);

    std::shared_ptr<AbstractFileLoaderCreator> create(std::string id);

private:
    CallbackMap callbacks;
};