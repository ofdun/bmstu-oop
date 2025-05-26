#include "CameraParserCSV.h"

#include <sstream>

#include "InvalidStreamException.h"
#include "NotImplementedException.h"
#include "cameraParser/CameraParserExceptions.h"

CameraParserCSV::CameraParserCSV(std::shared_ptr<std::istream> stream)
{
    this->stream = stream;
}

void CameraParserCSV::setStream(std::shared_ptr<std::istream> stream)
{
    this->stream = stream;
}

Point CameraParserCSV::getDirection()
{
    if (!stream || stream->fail())
        throw InvalidStreamException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    std::string in;
    char dummy;

    std::getline(*stream, in);

    std::istringstream iss(in);

    double x, y, z;

    if (!(iss >> x >> dummy >> y >> dummy >> z))
        throw InvalidCameraDirectionException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    return Point(x, y, z);
}

Point CameraParserCSV::getPosition()
{
    if (!stream || stream->fail())
        throw InvalidStreamException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    std::string in;
    char dummy;

    std::getline(*stream, in);

    std::istringstream iss(in);

    double x, y, z;

    if (!(iss >> x >> dummy >> y >> dummy >> z))
        throw InvalidCameraPositionException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    return Point(x, y, z);
}
