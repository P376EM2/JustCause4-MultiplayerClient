#pragma once

#include "GlobalVariables.h"
#include "Utils.h"


class HDevice_t;


class Graphics : public Singleton<Graphics>
{
  public:
    bool                           m_ready  = false;
    HDevice_t*                 m_device = nullptr;
    IFW1FontWrapper*               m_font   = nullptr;
    FW1FontWrapper::CFW1StateSaver m_state{};
    bool                           m_restoreState = false;

  public:
    static int64_t                                GraphicsFlipCallback(HDevice_t* device);
    static inline decltype(GraphicsFlipCallback)* pfn_Flip = nullptr;

  public:
    Graphics()  = default;
    ~Graphics() = default;

    void Shutdown();

    void DrawString(const std::string& str, float x, float y, float size, uint32_t color);
};
