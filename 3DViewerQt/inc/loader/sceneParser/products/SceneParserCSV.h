#pragma once

#include <memory>
#include <istream>

#include "AbstractSceneParser.h"

class SceneParserCSV : public AbstractSceneParser
{
public:
    ~SceneParserCSV() override = default;

    explicit SceneParserCSV(std::shared_ptr<std::istream> stream);

    objType getObjectType() override;

private:
    static std::unordered_map<std::string, objType> mp;
};