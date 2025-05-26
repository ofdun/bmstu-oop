#pragma once

#include <memory>
#include <istream>

#include "AbstractCameraParser.h"
#include "Point.h"

class CameraParserTXT : public AbstractCameraParser
{
public:
    ~CameraParserTXT() override = default;
    CameraParserTXT() = delete;
    explicit CameraParserTXT(std::shared_ptr<std::istream> stream);

    void setStream(std::shared_ptr<std::istream> stream) override;
    Point getDirection() override;
    Point getPosition() override;
};