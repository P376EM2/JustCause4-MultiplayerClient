#pragma once

#include <meow_hook/util.h>

#pragma pack(push, 1)

class CManagerBase
{
  public:
    static CManagerBase& instance()
    {
        return **(CManagerBase**)GetAddress(offsets::INST_INPUT_MANAGER);
    }

    void LoseFocus()
    {
        meow_hook::func_call<void>(GetAddress(offsets::INPUT_LOST_FOCUS), this);
    }

    void GainFocus()
    {
        meow_hook::func_call<void>(GetAddress(offsets::INPUT_GAIN_FOCUS), this);
    }
};
#pragma pack(pop)
