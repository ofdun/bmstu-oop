#pragma once

#include <memory>
#include <istream>

#include "AbstractModelParserCreator.h"
#include "ModelParserTXT.h"

class ModelParserTXTCreator : public AbstractModelParserCreator
{
public:
    ~ModelParserTXTCreator() override = default;

    std::shared_ptr<AbstractModelParser> create(std::shared_ptr<std::istream> stream) override
    {
        return std::make_shared<ModelParserTXT>(stream);
    }
};