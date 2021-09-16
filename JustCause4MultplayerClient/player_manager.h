#pragma once

#include "player.h"

#pragma pack(push, 1)
namespace jc
{
class CPlayerManager
{
  public:
    static CPlayerManager& instance()
    {
        return **(CPlayerManager**)GetAddress(offsets::INST_PLAYER_MANAGER);
    }

    static CCharacter* GetLocalPlayerCharacter()
    {
        auto inst = &instance();
        if (inst && inst->m_localPlayer && inst->m_localPlayer->m_character) {
            return inst->m_localPlayer->m_character;
        }

        return nullptr;
    }

  public:
    char     _pad[0x30];
    CPlayer* m_localPlayer;
};
}; // namespace jc
#pragma pack(pop)
