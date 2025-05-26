#pragma once

#include "AbstractObject.h"
#include "AbstractVisitor.h"

class Object : public AbstractObject
{
public:
    ~Object() override = default;

    void accept(std::shared_ptr<AbstractVisitor> visitor) override;
};