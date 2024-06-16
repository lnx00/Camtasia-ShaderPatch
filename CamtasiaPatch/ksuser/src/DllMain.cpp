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

using TGetterFunction = bool();
using TSetterFunction = void(bool bValue);

bool PatchFunction(void* targetFunction, const BYTE* customBytes, SIZE_T customSize)
{
	DWORD flOldProtect;

	// Change memory protection to allow writing
	if (VirtualProtect(targetFunction, customSize, PAGE_EXECUTE_READWRITE, &flOldProtect))
	{
		// Apply the custom byte sequence
		std::memcpy(targetFunction, customBytes, customSize);

		// Restore the original memory protection
		return VirtualProtect(targetFunction, customSize, flOldProtect, &flOldProtect);
	}

	MessageBox(nullptr, TEXT("Failed to patch function!"), TEXT("Error"), 0);
	return false;
}

DWORD WINAPI MainThread(LPVOID lpParam)
{
	// Wait for the target module
	HMODULE target_module = nullptr;
	while (!target_module)
	{
		Sleep(100);
		target_module = GetModuleHandleA("CSMediaLib.dll");
	}

	// Find the target function
	auto* target_function = reinterpret_cast<TGetterFunction*>(GetProcAddress(target_module, "?isSkipShaderSourceSignatureVerificationOn@FeatureSwitchSettings@CSMediaLib@@SA_NXZ"));
	if (!target_function)
	{
		MessageBoxA(nullptr, "Target function not found!", "Error", MB_ICONERROR | MB_OK);
		ExitThread(EXIT_SUCCESS);
	}

	// Apply the patch
	const BYTE patch_bytes[] = {
		0xB8, 0x01, 0x00, 0x00, 0x00, // mov eax, 1
		0xC3 // retn
	};
	if (!PatchFunction(target_function, patch_bytes, sizeof(patch_bytes)))
	{
		MessageBoxA(nullptr, "Patch failed!", "Error", MB_ICONERROR | MB_OK);
	}

	ExitThread(EXIT_SUCCESS);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			if (const HANDLE thread = CreateThread(nullptr, 0, MainThread, hinstDLL, 0, nullptr))
			{
				CloseHandle(thread);
			}
			break;
		}

		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}
