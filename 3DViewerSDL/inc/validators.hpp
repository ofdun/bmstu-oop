#ifndef VALIDATORS_HPP__
#define VALIDATORS_HPP__

#include "errors.hpp"

#include <stdio.h>

errCode validateCmdArgs(int argc, const char **argv);
errCode fileReadable(const char *filename, const char *format);

#endif // VALIDATORS_HPP__
