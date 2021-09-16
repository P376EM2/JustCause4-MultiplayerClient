#pragma once

#include "Offsets.h"

#pragma pack(push, 1)

class CClock
{
  public:
    static CClock& instance()
    {
        return **(CClock**)GetAddress(offsets::INST_CLOCK);
    }

  public:
    char _pad[0x30];
    bool m_paused;
};
#pragma pack(pop)
