#include "ModelParserCSV.h"

#include <sstream>

#include "InvalidStreamException.h"
#include "NotImplementedException.h"
#include "modelParser/ModelParserExceptions.h"

ModelParserCSV::ModelParserCSV(std::shared_ptr<std::istream> stream)
{
    this->stream = stream;
}

void ModelParserCSV::setStream(std::shared_ptr<std::istream> stream)
{
    this->stream = stream;
}

bool ModelParserCSV::anyEdgesLeft()
{
    if (!stream || stream->fail())
        throw InvalidStreamException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    std::string in;
    std::string type;
    char dummy;

    std::streampos pos = stream->tellg();

    std::getline(*stream, in);

    stream->seekg(pos);

    std::istringstream iss(in);

    double x, y;

    if (!(iss >> x >> dummy >> y >> dummy >> dummy >> type))
        return false;

    return type == "Edge";
}

bool ModelParserCSV::anyPointsLeft()
{
    if (!stream || stream->fail())
        throw InvalidStreamException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    std::string in;
    std::string type;
    char dummy;

    std::streampos pos = stream->tellg();

    std::getline(*stream, in);

    stream->seekg(pos);

    std::istringstream iss(in);

    double x, y, z;

    if (!(iss >> x >> dummy >> y >> dummy >> z >> dummy >> type))
        return false;

    return type == "Point";
}

Point ModelParserCSV::getNextPoint()
{
    if (!stream || stream->fail())
        throw InvalidStreamException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    std::string in;
    std::string type;
    char dummy;

    std::getline(*stream, in);

    std::istringstream iss(in);

    double x, y, z;

    if (!(iss >> x >> dummy >> y >> dummy >> z))
        throw InvalidPointFromStreamException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    return Point(x, y, z);
}

Edge ModelParserCSV::getNextEdge()
{
    if (!stream || stream->fail())
        throw InvalidStreamException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    std::string in;
    std::string type;
    char dummy;

    std::getline(*stream, in);

    std::istringstream iss(in);

    double x, y;

    if (!(iss >> x >> dummy >> y))
        throw InvalidPointFromStreamException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    return Edge(x, y);
}

