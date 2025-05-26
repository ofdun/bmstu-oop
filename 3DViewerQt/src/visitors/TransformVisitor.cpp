#include "TransformVisitor.h"

#include "Model.h"

void TransformVisitor::visit(Model &model)
{
    auto impl = model.impl;
    impl->transform(transformationMatrix);
}

void TransformVisitor::visit(PlainCamera &camera)
{
    auto impl = camera.impl;
    impl->transform(transformationMatrix);
}

