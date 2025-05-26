#include "SceneParserTXT.h"

#include "InvalidStreamException.h"

std::unordered_map<std::string, objType> SceneParserTXT::mp = {
    {"Model", MODEL},
    {"Camera", CAMERA},
};

SceneParserTXT::SceneParserTXT(std::shared_ptr<std::istream> stream)
{
    this->stream = stream;
}

objType SceneParserTXT::getObjectType()
{
    if (!stream || stream->fail())
        throw InvalidStreamException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    std::string in;
    std::getline(*stream, in);

    if (!mp.contains(in))
        return NONE;
    return mp[in];
}

