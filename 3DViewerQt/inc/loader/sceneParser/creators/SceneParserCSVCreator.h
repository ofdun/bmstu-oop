#pragma once

#include "AbstractSceneParserCreator.h"
#include "sceneParser/products/SceneParserCSV.h"

class SceneParserCSVCreator : public AbstractSceneParserCreator
{
public:
    ~SceneParserCSVCreator() override = default;

    std::shared_ptr<AbstractSceneParser> create(std::shared_ptr<std::istream> stream) override
    {
        return std::make_shared<SceneParserCSV>(stream);
    };
};