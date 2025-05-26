#include "ObjectSelector.h"

#include "EdgeListModelBuilder.h"
#include "MatrixModelBuilder.h"
#include "PlainCamera.h"

ObjectSelector::ObjectSelector(std::shared_ptr<AbstractModelDirector> modelDirector,
                               std::shared_ptr<CameraDirector> cameraDirector)
{
    directors = {
        {MODEL, [modelDirector]() {
            return modelDirector->create(std::make_shared<EdgeListModelBuilder>());
        }},
        {CAMERA, [cameraDirector]() {
            return cameraDirector->create(std::make_shared<CameraBuilder>());
        }},
    };
}

PtrObject ObjectSelector::create(objType type)
{
    return directors[type]();
}
