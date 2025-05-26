#pragma once

#include "AbstractManager.h"
#include "AbstractObject.h"
#include "Matrix.h"
#include "SelectManager.h"

class TransformManager : public AbstractManager
{
public:
    ~TransformManager() override = default;

    void transform(const Matrix<double> &transformationMatrix);
    void setSelectManager(std::shared_ptr<SelectManager> selectManager);

private:
    std::shared_ptr<SelectManager> selectManager;
};