#pragma once

#include <Windows.h>
#include <array>
#include <cstdint>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include <list>
#include <map>
#include <chrono>

#include "Singleton.h"

#define MESSAGE_HISTORY 100

#define MESSAGE_HISTORY_TO_DISPLAY 10

struct chatMessageStruct
{
    std::string chatMessage;
    unsigned long ulColor;
};

struct newChatMessageStruct
{
    std::string chatMessage;
    unsigned long uColor;
    std::chrono::time_point<std::chrono::steady_clock> received;

};

class InGameChat : public Singleton<InGameChat>
{

private:
    bool drawInGameChat = false;

    chatMessageStruct chatMessages[MESSAGE_HISTORY];

    std::string userTypedMessage;

    std::list<std::string> messageHistory;
    newChatMessageStruct newMessageHistory;

    using Clock = std::chrono::high_resolution_clock;

    std::chrono::time_point<std::chrono::steady_clock> now;
    std::chrono::milliseconds duration;

public:
    InGameChat();
    virtual ~InGameChat() = default;

    void onConnectionLost();
    void onConnectionReset();
    void onSendMessage(std::string message);
    void onMessageReceived(std::string message);

    void EnableInGameChat(bool toggle);
    bool IsInGameChatEnabled() const
    {
        return drawInGameChat;
    }

    void updateMessageHistory(std::string message);

    void Draw();
    bool FeedEvent(uint32_t message, WPARAM wParam, LPARAM lParam);
};
