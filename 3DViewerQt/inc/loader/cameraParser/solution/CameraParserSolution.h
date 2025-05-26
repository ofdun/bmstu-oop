#pragma once

#include <memory>
#include <filesystem>
#include <unordered_map>

#include "AbstractCameraParserCreator.h"

class CameraParserSolution
{
    using CreateCreator = std::shared_ptr<AbstractCameraParserCreator> (*)();
    using CallbackMap = std::unordered_map<std::string, CreateCreator>;

public:
    CameraParserSolution() = default;
    CameraParserSolution(std::initializer_list<std::pair<std::string, CreateCreator>> list);

    bool registrate(std::string id, CreateCreator creationFunc);
    bool remove(std::string id);

    std::shared_ptr<AbstractCameraParserCreator> create(std::string id);

private:
    CallbackMap callbacks;
};