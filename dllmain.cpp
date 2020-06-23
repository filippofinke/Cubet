#include <Windows.h>
#include "Cubet.h"
#include "Logger.h"

BOOL APIENTRY DllMain(HMODULE module, DWORD call, LPVOID lpReserved)
{
    LOG_DEBUG("%s", __FUNCTION__);
 
    if (call == DLL_PROCESS_ATTACH) {
        Cubet::Start(module);
    }

    DisableThreadLibraryCalls(module);
    return TRUE;
}

