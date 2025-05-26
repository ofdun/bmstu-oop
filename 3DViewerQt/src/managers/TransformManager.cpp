#include "TransformManager.h"

#include "TransformVisitor.h"

void TransformManager::transform(const Matrix<double> &transformationMatrix)
{
    std::shared_ptr<AbstractVisitor> visitor = std::make_shared<TransformVisitor>(transformationMatrix);
    auto composite = selectManager->getSelected();

    for (auto it = composite->begin(); it != composite->end(); ++it)
        it->get()->accept(visitor);
}

void TransformManager::setSelectManager(std::shared_ptr<SelectManager> selectManager)
{
    this->selectManager = selectManager;
}
