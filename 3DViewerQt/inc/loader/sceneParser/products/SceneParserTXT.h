#pragma once

#include <memory>
#include <istream>

#include "AbstractSceneParser.h"

class SceneParserTXT : public AbstractSceneParser
{
public:
    ~SceneParserTXT() override = default;

    explicit SceneParserTXT(std::shared_ptr<std::istream> stream);

    objType getObjectType() override;

private:
    static std::unordered_map<std::string, objType> mp;
};