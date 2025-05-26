#include "ManagerSolution.h"

#include "SolutionExceptions.h"

ManagerSolution::ManagerSolution(std::initializer_list<std::pair<managerType, CreateCreator>> list)
{
    for (const auto &e : list)
        registrate(e.first, e.second);
}

bool ManagerSolution::registrate(managerType id, CreateCreator creationFunc)
{
    return callbacks.insert(CallbackMap::value_type(id, creationFunc)).second;
}

bool ManagerSolution::remove(managerType id)
{
    return callbacks.erase(id) == 1;
}

std::shared_ptr<AbstractManagerCreator> ManagerSolution::create(managerType id)
{
    if (!callbacks.contains(id))
        throw NotRegisteredInSolutionException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    return std::shared_ptr(callbacks[id]());
}
