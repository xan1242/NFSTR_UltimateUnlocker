//
// Need for Speed The Run - Ultimate Unlocker / Unlock All Things
// by Xan / Tenjoin
//

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <thread>
#include "includes/injector/injector.hpp"
#include "includes/injector/assembly.hpp"

// int retZeroInt()
// {
// 	return 0;
// }

void Init()
{
	injector::MakeNOP(0x834303, 2);
	injector::MakeNOP(0x83434F, 2);

	injector::WriteMemory<uint8_t>(0x25A35EC, 0, true);
	injector::WriteMemory<uint8_t>(0x25A362E, 0, true);
	injector::WriteMemory<uint8_t>(0x25A363E, 0, true);

	uintptr_t loc_93E00D = 0x93E00D;
	struct CarUnlockHook1
	{
		void operator()(injector::reg_pack& regs)
		{
			*(uint8_t*)(regs.ecx + 0x18) = 1;
		}
	}; injector::MakeInline<CarUnlockHook1>(loc_93E00D, loc_93E00D + 6);
	injector::MakeJMP(loc_93E00D + 6, 0x93E0D8);

	uintptr_t loc_93F214 = 0x93F214;
	struct CarUnlockHook2
	{
		void operator()(injector::reg_pack& regs)
		{
			*(uint8_t*)(regs.ebp + 0x18) = 1;
		}
	}; injector::MakeInline<CarUnlockHook2>(loc_93F214, loc_93F214 + 6);
	injector::MakeJMP(loc_93F214 + 6, 0x93F2A0);

	// stage select unlock
	injector::MakeNOP(0x930C00, 2);
	injector::MakeNOP(0x9313A2, 2);

	// other modifications done by ALI (disables online?)
	// injector::MakeNOP(0xDD76CB, 2); // something with network?
	// Ebisu / Autolog stuff
	// injector::MakeJMP(0x018AEF80, retZeroInt);
	// injector::MakeJMP(0x018AF060, retZeroInt);
	// injector::MakeJMP(0x018AF0E0, retZeroInt);
	// injector::MakeJMP(0x018AF160, retZeroInt);
	// injector::MakeJMP(0x018AF1E0, retZeroInt);
	// injector::MakeJMP(0x018AF260, retZeroInt);
	// injector::MakeJMP(0x018AF2D0, retZeroInt);
	// injector::MakeJMP(0x018AF340, retZeroInt);
	// injector::MakeJMP(0x018AF3A0, retZeroInt);
	// injector::MakeJMP(0x018AF3A0, retZeroInt);
	// injector::MakeJMP(0x018AF420, retZeroInt);
	// injector::MakeJMP(0x018AF460, retZeroInt);
	// injector::MakeJMP(0x018AF4A0, retZeroInt);
	// injector::MakeJMP(0x018AF520, retZeroInt);
	// injector::MakeJMP(0x018AF5B0, retZeroInt);
	// injector::MakeJMP(0x018AF640, retZeroInt);

}

BOOL APIENTRY DllMain(HMODULE /*hModule*/, DWORD reason, LPVOID /*lpReserved*/)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		Init();
	}
	return TRUE;
}
