#include "SceneParserSolution.h"

#include "SolutionExceptions.h"

SceneParserSolution::SceneParserSolution(std::initializer_list<std::pair<std::string, CreateCreator>> list)
{
    for (const auto &e : list)
        registrate(e.first, e.second);
}

bool SceneParserSolution::registrate(std::string id, CreateCreator creationFunc)
{
    return callbacks.insert(CallbackMap::value_type(id, creationFunc)).second;
}

bool SceneParserSolution::remove(std::string id)
{
    return callbacks.erase(id) == 1;
}

std::shared_ptr<AbstractSceneParserCreator> SceneParserSolution::create(std::string id)
{
    if (!callbacks.contains(id))
        throw NotRegisteredInSolutionException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    return std::shared_ptr(callbacks[id]());
}
