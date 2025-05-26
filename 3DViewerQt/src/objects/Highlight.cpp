#include "Highlight.h"

bool Highlight::isComposite() const
{
    return true;
}

AbstractObject::iterator Highlight::begin()
{
    return container.begin();
}

AbstractObject::iterator Highlight::end()
{
    return container.end();
}

AbstractObject::const_iterator Highlight::begin() const
{
    return container.begin();
}

AbstractObject::const_iterator Highlight::end() const
{
    return container.end();
}

AbstractObject::const_iterator Highlight::cbegin() const
{
    return begin();
}

AbstractObject::const_iterator Highlight::cend() const
{
    return end();
}

bool Highlight::add(std::initializer_list<PtrObject> lst)
{
    for (const auto &obj : lst)
        if (obj)
            container.push_back(obj);

    return true;
}

bool Highlight::remove(size_t id)
{
    auto toDelete = iterator();
    bool found = false;
    for (auto it = begin(); it != end() && !found; ++it)
        if (it->get()->id() == id)
        {
            toDelete = it;
            found = true;
        }

    if (!found)
        return false;

    container.erase(toDelete);

    return true;
}

void Highlight::accept(std::shared_ptr<AbstractVisitor> visitor)
{
    for (const auto &obj : container)
        obj->accept(visitor);
}

