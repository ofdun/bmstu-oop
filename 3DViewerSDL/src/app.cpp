#include "app.hpp"

errCode runPolling(graphics &graphics)
{
    errCode rc = ERR_OK;
    bool ended = false;
    bool transformStateChanged = false;
    
    if (rc == ERR_OK)
        rc = handler_sendRequestRender(graphics);

    while (!ended && rc == ERR_OK)
    {
        graphics_eventHandler(ended);
        
        transform newTransformState = utils_parseTransformFromKeyPresses(transformStateChanged);
        if (!transformStateChanged) { }
        else
        {
            rc = handler_sendRequestTransform(newTransformState);

            if (rc == ERR_OK)
                rc = handler_sendRequestRender(graphics);
        }
        
        graphics_delay(DELAY);
    }

    handler_sendRequestDestroy();

    if (rc != ERR_OK)
        utils_printError(rc);

    return rc;
}
