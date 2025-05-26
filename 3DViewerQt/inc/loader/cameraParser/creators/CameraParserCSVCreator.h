#pragma once

#include <memory>
#include <istream>

#include "AbstractCameraParserCreator.h"
#include "CameraParserCSV.h"

class CameraParserCSVCreator : public AbstractCameraParserCreator
{
public:
    ~CameraParserCSVCreator() override = default;

    std::shared_ptr<AbstractCameraParser> create(std::shared_ptr<std::istream> stream) override
    {
        return std::make_shared<CameraParserCSV>(stream);
    }
};