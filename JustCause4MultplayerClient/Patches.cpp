#include "patches.h"
#include "offsets.h"

#include "clock.h"

#include "graphics.h"
#include "input.h"
#include "InGameChat.h"

#include <meow_hook/detour.h>
#include <meow_hook/memory.h>


LRESULT WndProc(HWND, UINT, WPARAM, LPARAM);

static decltype(WndProc)* pfn_WndProc = nullptr;

LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    const auto &inGameChat = InGameChat::Get();

    const uint32_t game_state   = *(uint32_t *)GetAddress(offsets::VAR_GAME_STATE);
    const bool     suspend_game = *(bool *)GetAddress(offsets::VAR_SUSPEND_GAME);
    auto           clock        = &CClock::instance();

    if (game_state == 3 && clock) {
		if (!suspend_game && !clock->m_paused)
		{
			if (inGameChat->FeedEvent(msg, wParam, lParam)) return 0;
		}
		else if (inGameChat->IsInGameChatEnabled())
		{
			inGameChat->EnableInGameChat(false);
		}
    }

    return pfn_WndProc(hwnd, msg, wParam, lParam);
}



bool InitPatchesAndHooks()
{
    // basic sanity check, ensure the game version is what we are expecting.
    // this will prevent crashes if the game updates, but someone is using an old version of this mod.
    if (strcmp((const char *)GetAddress(offsets::SANITY_CHECK), "Avalanche Engine") != 0) {
#ifdef DEBUG
        __debugbreak();
#endif
        return false;
    }

#ifdef DEBUG
    bool quick_start = true;
#else
    bool quick_start = (strstr(GetCommandLine(), "-quickstart") != nullptr);
#endif

    // enable quick start
    if (quick_start) {
        meow_hook::put(GetAddress(offsets::VAR_QUICK_START), true);
        meow_hook::put(GetAddress(offsets::IS_INTRO_SEQUENCE_COMPLETE), 0x90C301B0);
        meow_hook::put(GetAddress(offsets::IS_INTRO_MOVIE_COMPLETE), 0x90C301B0);
    }

    // WndProc
    pfn_WndProc = MH_STATIC_DETOUR(GetAddress(offsets::WND_PROC), WndProc);

    // Graphics::Flip
    Graphics::pfn_Flip = MH_STATIC_DETOUR(GetAddress(offsets::GRAPHICS_FLIP), Graphics::GraphicsFlipCallback);
    return true;
}
