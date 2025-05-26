#include "Model.h"

void Model::accept(std::shared_ptr<AbstractVisitor> visitor)
{
    visitor->visit(*this);
}
