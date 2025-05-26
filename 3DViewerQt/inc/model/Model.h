#pragma once

#include "AbstractModelImplementation.h"
#include "AbstractVisitor.h"
#include "Object.h"

class Model : public Object
{
private:
    friend class ProjectionVisitor;
    friend class TransformVisitor;
    friend class RenderVisitor;

public:
    ~Model() override = default;

    explicit Model(std::shared_ptr<AbstractModelImplementation> impl) : impl(impl)
    {
    }

    void accept(std::shared_ptr<AbstractVisitor> visitor) override;

private:
    std::shared_ptr<AbstractModelImplementation> impl;
};