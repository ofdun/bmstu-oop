#pragma once

#include "AbstractModelParser.h"

class ModelParserCSV : public AbstractModelParser
{
public:
    ~ModelParserCSV() override = default;

    explicit ModelParserCSV(std::shared_ptr<std::istream> stream);

    void setStream(std::shared_ptr<std::istream> stream) override;
    bool anyPointsLeft() override;
    bool anyEdgesLeft() override;
    Point getNextPoint() override;
    Edge getNextEdge() override;
};