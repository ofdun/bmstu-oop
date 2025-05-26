#pragma once

#include <vector>

#include "AbstractObject.h"
#include "AbstractVisitor.h"

class Highlight : public AbstractObject
{
public:
    ~Highlight() override = default;

    [[nodiscard]] bool isComposite() const override;

    [[nodiscard]] iterator begin() override;
    [[nodiscard]] iterator end() override;
    [[nodiscard]] const_iterator begin() const override;
    [[nodiscard]] const_iterator end() const override;
    [[nodiscard]] const_iterator cbegin() const override;
    [[nodiscard]] const_iterator cend() const override;

    bool add(std::initializer_list<PtrObject> lst) override;
    bool remove(size_t id) override;
    void accept(std::shared_ptr<AbstractVisitor> visitor) override;

private:
    std::vector<PtrObject> container;
};