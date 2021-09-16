#pragma once

#include "command.h"

class WorldCommand : public ICommand
{
  public:
    virtual const char* GetCommand() override
    {
        return "world";
    }

    virtual std::pair<bool, std::string> Handler(const std::string& arguments) override
    {
        using namespace jc;

        static auto hnpkWorld = *(void**)GetAddress(offsets::INST_HNPKWORLD);
        static auto WorldTime = *(void**)GetAddress(offsets::INST_WORLDTIME);

        static constexpr float DEFAULT_GRAVITY = -9.810f;

        // time
        if (arguments.find("time ") != std::string::npos) {
            float time = 0.0f;
            if (sscanf_s(arguments.c_str(), "time %f", &time) == 1) {
                time = std::clamp(time, -24.0f, 24.0f);
                meow_hook::func_call<void>(GetAddress(offsets::WORLDTIME_SET_TIME), WorldTime, time, 2);
                return {true, ""};
            }
        }
        // time scale
        else if (arguments.find("timescale ") != std::string::npos) {
            float timescale = 1.0f;
            if (sscanf_s(arguments.c_str(), "timescale %f", &timescale) == 1) {
                *(float*)((char*)WorldTime + 0xE4) = std::clamp(timescale, -1000.0f, 1000.0f);
                return {true, ""};
            }
        }
        // gravity
        else if (arguments.find("gravity ") != std::string::npos) {
            float gravity = DEFAULT_GRAVITY;
            if (sscanf_s(arguments.c_str(), "gravity %f", &gravity) == 1) {
                *(float*)((char*)hnpkWorld + 0x974) = std::clamp(gravity, -5000.0f, 5000.0f);
                return {true, ""};
            }
        }
        // reset gravity
        else if (arguments.find("resetgravity") != std::string::npos) {
            *(float*)((char*)hnpkWorld + 0x974) = DEFAULT_GRAVITY;
            return {true, ""};
        }

        return {false, ""};
    }

    virtual std::vector<std::string> GetHints(const std::string& arguments) override
    {
        static std::array hints{
            "time",
            "timescale",
            "gravity",
            "resetgravity",
        };

        std::vector<std::string> result;
        std::copy_if(hints.begin(), hints.end(), std::back_inserter(result),
                     [&](const std::string& item) { return item.find(arguments) != std::string::npos; });

        return result;
    }
};
