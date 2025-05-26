#pragma once


#include <memory>
#include <filesystem>
#include <unordered_map>

#include "AbstractModelParserCreator.h"

class ModelParserSolution
{
    using CreateCreator = std::shared_ptr<AbstractModelParserCreator> (*)();
    using CallbackMap = std::unordered_map<std::string, CreateCreator>;

public:
    ModelParserSolution() = default;
    ModelParserSolution(std::initializer_list<std::pair<std::string, CreateCreator>> list);

    bool registrate(std::string id, CreateCreator creationFunc);
    bool remove(std::string id);

    std::shared_ptr<AbstractModelParserCreator> create(std::string id);

private:
    CallbackMap callbacks;
};