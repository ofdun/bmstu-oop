#include "ModelParserTXT.h"

#include "InvalidStreamException.h"
#include "modelParser/ModelParserExceptions.h"

#include <sstream>

ModelParserTXT::ModelParserTXT(std::shared_ptr<std::istream> stream)
{
    this->stream = stream;
}

void ModelParserTXT::setStream(std::shared_ptr<std::istream> stream)
{
    this->stream = stream;
}

bool ModelParserTXT::anyEdgesLeft()
{
    if (!stream || stream->fail())
        throw InvalidStreamException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    std::streampos pos = stream->tellg();

    std::string in;
    std::getline(*stream, in);

    stream->seekg(pos);

    std::istringstream iss(in);
    size_t a, b;

    if (!(iss >> a >> b))
    {
        stream->clear();
        return false;
    }

    return true;
}

bool ModelParserTXT::anyPointsLeft()
{
    if (!stream || stream->fail())
        throw InvalidStreamException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    std::streampos pos = stream->tellg();

    std::string in;
    std::getline(*stream, in);

    stream->seekg(pos);

    std::istringstream iss(in);
    double a, b, c;

    if (!(iss >> a >> b >> c))
    {
        stream->clear();
        return false;
    }

    return true;
}

Edge ModelParserTXT::getNextEdge()
{
    if (!stream || stream->fail())
        throw InvalidStreamException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    std::string in;
    std::getline(*stream, in);

    std::istringstream iss(in);
    size_t a, b;

    if (!(iss >> a >> b))
        throw InvalidEdgeFromStreamException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    return Edge(a, b);
}

Point ModelParserTXT::getNextPoint()
{
    if (!stream || stream->fail())
        throw InvalidStreamException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    std::string in;
    std::getline(*stream, in);

    std::istringstream iss(in);
    double a, b, c;

    if (!(iss >> a >> b >> c))
        throw InvalidPointFromStreamException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    return Point(a, b, c);
}

