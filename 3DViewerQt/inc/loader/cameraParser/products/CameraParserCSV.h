#pragma once
#include "AbstractCameraParser.h"

class CameraParserCSV : public AbstractCameraParser
{
public:
    ~CameraParserCSV() override = default;
    CameraParserCSV() = delete;
    explicit CameraParserCSV(std::shared_ptr<std::istream> stream);

    void setStream(std::shared_ptr<std::istream> stream) override;
    Point getDirection() override;
    Point getPosition() override;
};