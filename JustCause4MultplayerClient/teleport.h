#pragma once

#include "command.h"
#include "Utils.h"

class TeleportCommand : public ICommand
{
  private:
    util::KeyValueFile m_saveFile;

  public:
    virtual const char* GetCommand() override
    {
        return "tp";
    }

    virtual void Init() override
    {
        m_saveFile.load("savedcoords.txt");
    }

    virtual std::pair<bool, std::string> Handler(const std::string& arguments) override
    {
        if (arguments.find("save ") != std::string::npos) {
            char name[128] = {0};
            if (sscanf_s(arguments.c_str(), "save %[^\n]s", &name, 128) == 1) {
                auto& transform = jc::CPlayerManager::instance().GetLocalPlayerCharacter()->m_worldTransform;
                m_saveFile.set(name, "%f %f %f", transform.m[3].x, transform.m[3].y, transform.m[3].z);
                return {true, ""};
            }
        } else if (arguments.find("delete ") != std::string::npos) {
            char name[128] = {0};
            if (sscanf_s(arguments.c_str(), "delete %[^\n]s", &name, 128) == 1) {
                m_saveFile.remove(name);
                return {true, ""};
            }
        } else if (arguments.find("printpos") != std::string::npos) {
            auto&             transform = jc::CPlayerManager::instance().GetLocalPlayerCharacter()->m_worldTransform;
            const std::string pos = std::to_string((int)transform.m[3].x) + " " + std::to_string((int)transform.m[3].y)
                                    + " " + std::to_string((int)transform.m[3].z);
            return {true, pos};
        } else if (arguments.find("get") != std::string::npos) {
            char name[128] = {0};
            if (sscanf_s(arguments.c_str(), "get %[^\n]s", &name, 128) == 1) {
                CVector3f position;
                if (m_saveFile.get(name, "%f %f %f", &position.x, &position.y, &position.z)) {
                    const std::string pos = std::to_string((int)position.x) + " " + std::to_string((int)position.y)
                                            + " " + std::to_string((int)position.z);
                    return {true, pos};
                } else {
                    return {false, ""};
                }
            }
        } else {
            static auto Teleport = [](CVector3f& position) {
                // @FUNFACT: game will crash if you teleport to 0,x,0
                if (position.x == 0 && position.z == 0) {
                    position.x = 1.0f;
                    position.z = 1.0f;
                }

                CMatrix4f world{};
                world.m[3].x = position.x;
                world.m[3].y = position.y;
                world.m[3].z = position.z;

                jc::CGameWorld::instance().TeleportPlayer(&world, nullptr, false, false, 0.0f, 0.0f, 0, nullptr, false,
                                                          nullptr);
            };

            // try read coords straight from input (e.g. tp [x] [y] [z])
            CVector3f position;
            if (sscanf_s(arguments.c_str(), "%f %f %f", &position.x, &position.y, &position.z) == 3) {
                Teleport(position);
                return {true, ""};
            }
            // try read saved position from coords file
            else {
                char name[128] = {0};
                if (sscanf_s(arguments.c_str(), "%[^\n]s", &name, 128) == 1) {
                    if (m_saveFile.get(name, "%f %f %f", &position.x, &position.y, &position.z)) {
                        Teleport(position);
                        return {true, ""};
                    }
                }
            }
        }

        return {false, ""};
    }

    virtual std::vector<std::string> GetHints(const std::string& arguments) override
    {
        static std::array hints{
            "save",
            "delete",
			"printpos", 
			"get"
        };

        std::vector<std::string> result;
        std::copy_if(hints.begin(), hints.end(), std::back_inserter(result),
                     [&](const std::string& item) { return item.find(arguments) != std::string::npos; });

        // copy saved coord names
        for (const auto& entry : m_saveFile.Values) {
            if (entry.first.find(arguments) != std::string::npos) {
                result.push_back(entry.first);
            }
        }

        return result;
    }
};
