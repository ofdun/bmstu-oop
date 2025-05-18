#include "errors.hpp"
#include "app.hpp"
#include "validators.hpp"

int main(int argc, const char **argv)
{
    errCode rc = validateCmdArgs(argc, argv);

    if (rc == ERR_OK)
        rc = handler_sendRequestInit(argv[1]);

    graphics graphics;
    if (rc == ERR_OK)
        rc = graphics_initGraphics(graphics);

    if (rc == ERR_OK)
        rc = runPolling(graphics);

    graphics_free(graphics);
    
    return rc;
}
