#pragma once

#include "TransformManager.h"
#include "AbstractCommand.h"

class MoveCommand : public AbstractCommand
{
private:
    using Action = void (TransformManager::*)(const Matrix<double> &);

public:
    ~MoveCommand() override = default;
    MoveCommand() = delete;

    MoveCommand(const Matrix<double> &m) : transformationMatrix(m)
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