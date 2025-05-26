#include "CameraParserTXT.h"

#include "InvalidStreamException.h"
#include "cameraParser/CameraParserExceptions.h"

#include <sstream>

CameraParserTXT::CameraParserTXT(std::shared_ptr<std::istream> stream)
{
    this->stream = stream;
}

void CameraParserTXT::setStream(std::shared_ptr<std::istream> stream)
{
    this->stream = stream;
}

Point CameraParserTXT::getDirection()
{
    if (!stream || stream->fail())
        throw InvalidStreamException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    std::string in;
    std::getline(*stream, in);

    std::istringstream iss(in);
    double x, y, z;

    if (!(iss >> x >> y >> z))
        throw InvalidCameraDirectionException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    return Point(x, y, z);
}

Point CameraParserTXT::getPosition()
{
    if (!stream || stream->fail())
        throw InvalidStreamException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    std::string in;
    std::getline(*stream, in);

    std::istringstream iss(in);
    double x, y, z;

    if (!(iss >> x >> y >> z))
        throw InvalidCameraPositionException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    return Point(x, y, z);
}
