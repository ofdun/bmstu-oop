#pragma once

#include <memory>
#include <unordered_map>

#include "enums.h"
#include "AbstractManagerCreator.h"

class ManagerSolution
{
    using CreateCreator = std::shared_ptr<AbstractManagerCreator> (*)();
    using CallbackMap = std::unordered_map<managerType, CreateCreator>;

public:
    ManagerSolution() = default;
    ManagerSolution(std::initializer_list<std::pair<managerType, CreateCreator>> list);

    bool registrate(managerType id, CreateCreator creationFunc);
    bool remove(managerType id);

    std::shared_ptr<AbstractManagerCreator> create(managerType id);

private:
    CallbackMap callbacks;
};