#pragma once

#include "Camera.h"
#include "PlainCameraImplementation.h"

class PlainCamera : public Camera
{
private:
    friend class ProjectionVisitor;
    friend class TransformVisitor;
    friend class RenderVisitor;

public:
    ~PlainCamera() override = default;

    explicit PlainCamera(std::shared_ptr<PlainCameraImplementation> imp) : impl(imp)
    {
    }

    void accept(std::shared_ptr<AbstractVisitor> visitor) override
    {
        visitor->visit(*this);
    }

private:
    std::shared_ptr<PlainCameraImplementation> impl;
};
