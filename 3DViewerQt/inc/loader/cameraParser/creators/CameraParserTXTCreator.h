#pragma once

#include <memory>
#include <istream>

#include "AbstractCameraParserCreator.h"
#include "CameraParserTXT.h"

class CameraParserTXTCreator : public AbstractCameraParserCreator
{
public:
    ~CameraParserTXTCreator() override = default;

    std::shared_ptr<AbstractCameraParser> create(std::shared_ptr<std::istream> stream) override
    {
        return std::make_shared<CameraParserTXT>(stream);
    }
};