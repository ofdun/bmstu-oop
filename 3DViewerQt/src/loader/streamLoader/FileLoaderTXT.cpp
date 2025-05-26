#include "FileLoaderTXT.h"

#include "FileLoaderExceptions.h"

FileLoaderTXT::FileLoaderTXT(const std::filesystem::path &path)
{
    this->path = path;
}

std::shared_ptr<std::ifstream> FileLoaderTXT::get()
{
    if (file == nullptr)
        open();

    return file;
}

void FileLoaderTXT::open()
{
    if (!exists(path))
        throw FileDoesNotExistException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    if (!is_regular_file(path))
        throw FileIsADirectoryException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    auto file_ = std::make_shared<std::ifstream>(path);
    if (!file_->is_open())
        throw FileIsNotOpeningException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    file = file_;
}

void FileLoaderTXT::close()
{
    if (file->is_open())
        file->close();
}