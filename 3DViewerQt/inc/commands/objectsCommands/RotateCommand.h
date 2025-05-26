#pragma once

#include "TransformManager.h"
#include "AbstractCommand.h"

class RotateCommand : public AbstractCommand
{
private:
    using Action = void (TransformManager::*)(const Matrix<double> &);

public:
    ~RotateCommand() override = default;
    RotateCommand() = delete;

    RotateCommand(const Matrix<double> &m) : transformationMatrix(m)
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