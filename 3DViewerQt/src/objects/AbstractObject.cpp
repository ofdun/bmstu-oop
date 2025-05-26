#include "AbstractObject.h"

size_t AbstractObject::count = 0;

AbstractObject::~AbstractObject() = default;


size_t AbstractObject::id() const
{
    return id_;
}

bool AbstractObject::isComposite() const
{
    return false;
}

AbstractObject::iterator AbstractObject::begin()
{
    return iterator();
}

AbstractObject::iterator AbstractObject::end()
{
    return iterator();
}


AbstractObject::const_iterator AbstractObject::begin() const
{
    return const_iterator();
}

AbstractObject::const_iterator AbstractObject::end() const
{
    return const_iterator();
}

AbstractObject::const_iterator AbstractObject::cbegin() const
{
    return begin();
}

AbstractObject::const_iterator AbstractObject::cend() const
{
    return end();
}

bool AbstractObject::add(std::initializer_list<PtrObject> lst)
{
    return false;
}

bool AbstractObject::remove(size_t id)
{
    return false;
}
