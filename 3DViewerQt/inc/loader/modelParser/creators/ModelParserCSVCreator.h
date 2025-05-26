#pragma once

#include <memory>
#include <istream>

#include "AbstractModelParserCreator.h"
#include "ModelParserCSV.h"

class ModelParserCSVCreator : public AbstractModelParserCreator
{
public:
    ~ModelParserCSVCreator() override = default;

    std::shared_ptr<AbstractModelParser> create(std::shared_ptr<std::istream> stream) override
    {
        return std::make_shared<ModelParserCSV>(stream);
    };
};