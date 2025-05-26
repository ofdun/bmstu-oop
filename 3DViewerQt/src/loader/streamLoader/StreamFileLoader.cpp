#include "StreamFileLoader.h"

#include <fstream>

StreamFileLoader::StreamFileLoader(std::shared_ptr<AbstractFileLoader> fileLoader)
{
    this->fileLoader = fileLoader;
}

std::shared_ptr<std::istream> StreamFileLoader::getStream()
{
    return fileLoader->get();
}


void StreamFileLoader::closeStream()
{
    fileLoader->close();
}

