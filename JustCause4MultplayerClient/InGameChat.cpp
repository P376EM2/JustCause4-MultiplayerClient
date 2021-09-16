#include <Windows.h>

#include "utils.h"

#include <iostream>

#include "Offsets.h"

#include "Graphics.h"

#include "InGameChat.h"

#include "InputManager.h"
#include "RenderEngine.h"

static constexpr int32_t NUM_HINTS_PER_PAGE = 10;
static constexpr float   HINT_ITEM_HEIGHT = 0.02f;
static constexpr float   FONT_SIZE_INPUT = 0.0155f;
static constexpr float   FONT_SIZE_HINT = 0.0133f;

InGameChat::InGameChat()
{
    newMessageHistory.chatMessage = "";

    for (int i = 0; i < MESSAGE_HISTORY; i++)
    {
        chatMessages[i].chatMessage[0] = '\0';
        chatMessages[i].ulColor = 0xFFFFFFFF;
    }
}

void InGameChat::onConnectionLost()
{
}

void InGameChat::onConnectionReset()
{
}

void InGameChat::onSendMessage(std::string message)
{
    std::cout << message << std::endl;
}

void InGameChat::onMessageReceived(std::string message)
{

}

void InGameChat::EnableInGameChat(bool toggle)
{
    drawInGameChat = toggle;

    if (toggle)
    {
        CManagerBase::instance().LoseFocus();
    }
    else
    {
        CManagerBase::instance().GainFocus();
    }
}

void InGameChat::updateMessageHistory(std::string message)
{
    if (messageHistory.size() >= MESSAGE_HISTORY) messageHistory.pop_back();
    
    messageHistory.push_front(message);
}

void InGameChat::Draw()
{
    auto debug_renderer = CRenderEngine::instance().m_debugRenderer;

    if (drawInGameChat && debug_renderer)
    {
        int i = 0;

        if (newMessageHistory.chatMessage != "")
        {
            now = Clock::now();

            duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - newMessageHistory.received);

            if (duration.count() <= 5000)
            {
                messageHistory.push_front(newMessageHistory.chatMessage);
                newMessageHistory.chatMessage = "";
            }
        }

        for (std::list<std::string> ::iterator history = messageHistory.begin(); history != messageHistory.end(); ++history)
        {
            if (i < MESSAGE_HISTORY_TO_DISPLAY)
            {
                Graphics::Get()->DrawString(*history, 0.0145f, (0.7f - (i * 0.0175f)), FONT_SIZE_INPUT, 0xFF0000FF);
            }
            
            i++;
        }

        debug_renderer->DebugRectGradient({ 0, 0.75f }, { 0.5f, 0.805f }, 0xE1000000, 0x00000000);

        Graphics::Get()->DrawString("Say: " + userTypedMessage, 0.0145f, 0.765f, FONT_SIZE_INPUT, 0xFF0000FF);
    }
    else
    {
        if (newMessageHistory.chatMessage != "")
        {
            now = Clock::now();

            duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - newMessageHistory.received);

            if (duration.count() <= 5000)
            {
                Graphics::Get()->DrawString(newMessageHistory.chatMessage, 0.0145f, (0.7f - (0.0175f)), FONT_SIZE_INPUT, 0xFF0000FF);
            }
        }
    }
}

bool InGameChat::FeedEvent(uint32_t message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_KEYDOWN:
        {
            const auto vsc = MapVirtualKeyEx(static_cast<int32_t>(wParam), MAPVK_VK_TO_VSC, GetKeyboardLayout(0));

            if ((vsc == 20 || vsc == 1) && (lParam >> 30) == 0)
            {
                if (!IsInGameChatEnabled() && vsc == 20)
                {
                    EnableInGameChat(true);

                    return true;
                }
                else if (IsInGameChatEnabled() && vsc == 1)
                {
                    EnableInGameChat(false);

                    return true;
                }            
            }

            if (drawInGameChat)
            {
                return true;
            }

            break;
        }

        case WM_CHAR:
        {
            if (drawInGameChat && wParam > 0 && wParam < 0x10000)
            {
                if (((lParam >> 16) & 0xff) == 41)
                {


                    break;
                }

                switch (wParam)
                {
                    case VK_RETURN:
                    {
                        onSendMessage(userTypedMessage);

                        updateMessageHistory(userTypedMessage);

                        userTypedMessage = "";

                        EnableInGameChat(false);
                        break;
                    }
                    case VK_BACK:
                    {
                        if (userTypedMessage.length() > 0) userTypedMessage = userTypedMessage.substr(0, userTypedMessage.size() - 1);

                        break;
                    }

                    default:
                    {
                     
                            if (userTypedMessage.length() < 256) userTypedMessage += (char)wParam;
                      

                        break;
                    }
                }
            }

            break;
        }
    }

    if (drawInGameChat) return true;

    return false;
}


