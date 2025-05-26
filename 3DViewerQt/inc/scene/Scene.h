#pragma once

#include "AbstractScene.h"

class Scene : public AbstractScene
{
public:
    ~Scene() override = default;

    iterator begin() const override;
    iterator end() const override;
    bool addObject(PtrObject obj) override;
    bool removeObject(size_t id) override;
};