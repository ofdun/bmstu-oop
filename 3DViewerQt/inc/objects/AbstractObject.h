#pragma once

#include <initializer_list>
#include <vector>

#include "AbstractVisitor.h"

class AbstractObject;

using PtrObject = std::shared_ptr<AbstractObject>;
using VectorObject = std::vector<PtrObject>;

class AbstractObject
{
public:
    using value_type = AbstractObject;
    using size_type = size_t;
    using iterator = VectorObject::iterator;
    using const_iterator = VectorObject::const_iterator;

    virtual ~AbstractObject() = 0;

    [[nodiscard]] virtual size_t id() const;

    [[nodiscard]] virtual bool isComposite() const;

    [[nodiscard]] virtual iterator begin();
    [[nodiscard]] virtual iterator end();
    [[nodiscard]] virtual const_iterator begin() const;
    [[nodiscard]] virtual const_iterator end() const;
    [[nodiscard]] virtual const_iterator cbegin() const;
    [[nodiscard]] virtual const_iterator cend() const;

    virtual bool add(std::initializer_list<PtrObject> lst);

    virtual bool remove(size_t id);

    virtual void accept(std::shared_ptr<AbstractVisitor> visitor) = 0;

protected:
    size_t id_ = count++;

private:
    static size_t count;
};