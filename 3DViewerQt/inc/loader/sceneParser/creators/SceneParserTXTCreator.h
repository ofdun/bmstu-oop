#pragma once

#include "AbstractSceneParserCreator.h"
#include "sceneParser/products/SceneParserTXT.h"

class SceneParserTXTCreator : public AbstractSceneParserCreator
{
public:
    ~SceneParserTXTCreator() override = default;

    std::shared_ptr<AbstractSceneParser> create(std::shared_ptr<std::istream> stream) override
    {
        return std::make_shared<SceneParserTXT>(stream);
    }
};