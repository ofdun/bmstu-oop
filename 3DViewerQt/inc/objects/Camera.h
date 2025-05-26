#pragma once

#include "AbstractObject.h"
#include "AbstractVisitor.h"

class Camera : public AbstractObject
{
public:
    ~Camera() override = default;

    void accept(std::shared_ptr<AbstractVisitor> visitor) override;
};
