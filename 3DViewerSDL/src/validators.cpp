#include "validators.hpp"

errCode validateCmdArgs(int argc, const char **argv)
{
    errCode rc = ERR_OK;

    if (argc != 2)
        rc = ERR_WRONG_ARGS;

    if (rc == ERR_OK)
        rc = fileReadable(argv[1], "r");

    return rc;
}

errCode fileReadable(const char *filename, const char *format)
{
    errCode rc = ERR_OK;

    FILE *f = fopen(filename, format);

    if (!f)
        rc = ERR_WRONG_FILE;
    else
        fclose(f);

    return rc;
}
