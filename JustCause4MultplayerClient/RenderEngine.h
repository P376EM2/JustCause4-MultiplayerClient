#pragma once

#include "DebugRenderer.h"

#pragma pack(push, 1)
class CRenderEngine
{
  public:
    static CRenderEngine& instance()
    {
        return **(CRenderEngine**)GetAddress(offsets::INST_RENDER_ENGINE);
    }

  public:
    char               _pad[0x2BC8];
    DebugRendererImpl* m_debugRenderer;
};
#pragma pack(pop)
