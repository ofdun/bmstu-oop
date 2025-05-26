#pragma once

#include "AbstractCameraParser.h"
#include "AbstractModelParser.h"

#include <memory>
#include <unordered_map>

#include "AbstractObject.h"
#include "CameraDirector.h"
#include "enums.h"
#include "builders/model/ModelBuilderDirectorSolution.h"

class ObjectSelector
{
public:
    ObjectSelector() = delete;

    ObjectSelector(std::shared_ptr<AbstractModelDirector> modelDirector,
                   std::shared_ptr<CameraDirector> cameraDirector);

    PtrObject create(objType type);

private:
    std::unordered_map<objType, std::function<PtrObject()>> directors;
};