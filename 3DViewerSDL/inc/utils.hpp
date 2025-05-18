#ifndef UTILS_HPP
#define UTILS_HPP

#include "graphics.hpp"
#include "transform.hpp"

transform utils_parseTransformFromKeyPresses(bool &changed);
offset utils_parseOffsetFromKeyPresses(bool &changed);
rotation utils_parseRotationFromKeyPresses(bool &changed);
scale utils_parseScaleFromKeyPresses(bool &changed);
transform utils_loadTransformInitPos();

void utils_printError(errCode rc);

#endif //UTILS_HPP
