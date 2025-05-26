#pragma once

#include <memory>
#include <filesystem>
#include <unordered_map>

#include "AbstractSceneParserCreator.h"

class SceneParserSolution
{
    using CreateCreator = std::shared_ptr<AbstractSceneParserCreator> (*)();
    using CallbackMap = std::unordered_map<std::string, CreateCreator>;

public:
    SceneParserSolution() = default;
    SceneParserSolution(std::initializer_list<std::pair<std::string, CreateCreator>> list);

    bool registrate(std::string id, CreateCreator creationFunc);
    bool remove(std::string id);

    std::shared_ptr<AbstractSceneParserCreator> create(std::string id);

private:
    CallbackMap callbacks;
};