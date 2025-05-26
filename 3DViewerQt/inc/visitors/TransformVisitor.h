#pragma once

#include "AbstractVisitor.h"
#include "PlainCamera.h"
#include "Matrix.h"

class TransformVisitor : public AbstractVisitor
{
public:
    ~TransformVisitor() override = default;

    TransformVisitor() = delete;

    explicit TransformVisitor(const Matrix<double> &m) : transformationMatrix(m)
    {
    }

    void visit(Model &model) override;
    void visit(PlainCamera &camera) override;

private:
    Matrix<double> transformationMatrix;
};