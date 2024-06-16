#pragma once

#pragma comment(linker,"/export:KsCreateAllocator=c:\\windows\\system32\\ksuser.KsCreateAllocator,@1")
#pragma comment(linker,"/export:KsCreateAllocator2=c:\\windows\\system32\\ksuser.KsCreateAllocator2,@2")
#pragma comment(linker,"/export:KsCreateClock=c:\\windows\\system32\\ksuser.KsCreateClock,@3")
#pragma comment(linker,"/export:KsCreateClock2=c:\\windows\\system32\\ksuser.KsCreateClock2,@4")
#pragma comment(linker,"/export:KsCreatePin=c:\\windows\\system32\\ksuser.KsCreatePin,@5")
#pragma comment(linker,"/export:KsCreatePin2=c:\\windows\\system32\\ksuser.KsCreatePin2,@6")
#pragma comment(linker,"/export:KsCreateTopologyNode=c:\\windows\\system32\\ksuser.KsCreateTopologyNode,@7")
#pragma comment(linker,"/export:KsCreateTopologyNode2=c:\\windows\\system32\\ksuser.KsCreateTopologyNode2,@8")

#include "windows.h"
#include "ios"
#include "fstream"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

