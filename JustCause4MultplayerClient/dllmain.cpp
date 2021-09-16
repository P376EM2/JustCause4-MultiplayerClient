#include "dllmain.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    // exit if not jc4
    if (!GetModuleHandle("JustCause4.exe") && !GetModuleHandle("JustCause4GameCL.exe")) {
        return FALSE;
    }

    switch (fdwReason) {
        case DLL_PROCESS_ATTACH: {
            char buffer[MAX_PATH] = {0};
            GetSystemDirectoryA(buffer, MAX_PATH);
            strcat_s(buffer, MAX_PATH, "\\xinput9_1_0.dll");

            g_original_module = LoadLibraryA(buffer);
            if (g_original_module) {
                XInputGetState_ = (XInputGetState_t)GetProcAddress(g_original_module, "XInputGetState");
                XInputSetState_ = (XInputSetState_t)GetProcAddress(g_original_module, "XInputSetState");
            }

            // just checking the module handle is probably enough, but w/e.
            bool isSteam = !strstr(GetCommandLine(), "-epicusername") && GetModuleHandle("steam_api64.dll");
            offsets::InitAddresses(isSteam);

            // something is wrong. sanity check failed. probably the game updated and offsets are wrong.
            if (!InitPatchesAndHooks()) {
                return TRUE;
            }

            break;
        }

        case DLL_PROCESS_DETACH: {
            if (g_original_module) {
                FreeLibrary(g_original_module);
            }

            break;
        }
    }

    return TRUE;
}
