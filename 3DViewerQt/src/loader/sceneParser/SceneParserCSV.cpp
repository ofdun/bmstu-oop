#include "SceneParserCSV.h"

#include <sstream>

#include "InvalidStreamException.h"
#include "NotImplementedException.h"

std::unordered_map<std::string, objType> SceneParserCSV::mp = {
    {"Model", MODEL},
    {"Camera", CAMERA},
};

SceneParserCSV::SceneParserCSV(std::shared_ptr<std::istream> stream)
{
    this->stream = stream;
}

objType SceneParserCSV::getObjectType()
{
    if (!stream || stream->fail())
        throw InvalidStreamException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    std::string in, type;
    char dummy;

    std::getline(*stream, in);

    std::istringstream iss(in);

    if (!(iss >> dummy >> dummy >> dummy >> type) || !mp.contains(type))
        return NONE;

    return mp[type];
}
