#pragma once

#include "TransformManager.h"
#include "AbstractCommand.h"

class ScaleCommand : public AbstractCommand
{
private:
    using Action = void (TransformManager::*)(const Matrix<double> &);

public:
    ~ScaleCommand() override = default;
    ScaleCommand() = delete;

    ScaleCommand(const Matrix<double> &m) : transformationMatrix(m)
    {
    }

    void execute() override
    {
        ((*transformManager).*action)(transformationMatrix);
    }

private:
    Action action = &TransformManager::transform;
    Matrix<double> transformationMatrix;
};