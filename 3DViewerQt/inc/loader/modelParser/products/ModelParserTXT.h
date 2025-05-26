#pragma once

#include "AbstractModelParser.h"

class ModelParserTXT : public AbstractModelParser
{
public:
    ~ModelParserTXT() override = default;

    explicit ModelParserTXT(std::shared_ptr<std::istream> stream);

    void setStream(std::shared_ptr<std::istream> stream) override;
    bool anyPointsLeft() override;
    bool anyEdgesLeft() override;
    Point getNextPoint() override;
    Edge getNextEdge() override;
};