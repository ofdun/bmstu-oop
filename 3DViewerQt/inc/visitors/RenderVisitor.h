#pragma once

#include "AbstractPainter.h"
#include "AbstractVisitor.h"
#include "Model.h"
#include "PlainCamera.h"

class RenderVisitor : public AbstractVisitor
{
public:
    ~RenderVisitor() override = default;

    explicit RenderVisitor(std::shared_ptr<AbstractPainter> painter, std::shared_ptr<Camera> camera) :
        camera(camera), painter(painter)
    {
    }

    void visit(Model &model) override;
    void visit(PlainCamera &camera) override;

private:
    std::shared_ptr<Camera> camera;
    std::shared_ptr<AbstractPainter> painter;
};