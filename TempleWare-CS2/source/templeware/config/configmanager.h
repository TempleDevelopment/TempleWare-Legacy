#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <cstdlib>

#include "config.h"
#include "../../../external/json/json.hpp"

namespace internal_config
{
    class ConfigManager
    {
    private:

        static std::filesystem::path GetConfigFolder()
        {
            char* userProfile = nullptr;
            size_t len = 0;
            errno_t err = _dupenv_s(&userProfile, &len, "USERPROFILE");

            std::filesystem::path folder;
            if (err != 0 || userProfile == nullptr || len == 0)
            {
                folder = ".templeware";
            }
            else
            {
                folder = userProfile;
                free(userProfile);
                folder /= ".templeware";
            }
            folder /= "internal";

            std::error_code ec;
            std::filesystem::create_directories(folder, ec);

            return folder;
        }

        static std::filesystem::path GetConfigPath(const std::string& configName)
        {
            auto folder = GetConfigFolder();
            return folder / (configName + ".json");
        }

    public:

        static std::vector<std::string> ListConfigs()
        {
            std::vector<std::string> list;
            auto folder = GetConfigFolder();
            if (!std::filesystem::exists(folder))
                return list;

            for (const auto& entry : std::filesystem::directory_iterator(folder))
            {
                if (entry.is_regular_file())
                {
                    auto path = entry.path();
                    if (path.extension() == ".json")
                    {
                        list.push_back(path.stem().string());
                    }
                }
            }
            return list;
        }

        static void Save(const std::string& configName)
        {
            nlohmann::json j;
            j["esp"] = Config::esp;
            j["showHealth"] = Config::showHealth;
            j["teamCheck"] = Config::teamCheck;
            j["espFill"] = Config::espFill;
            j["espThickness"] = Config::espThickness;
            j["espFillOpacity"] = Config::espFillOpacity;
            j["espColor"] = {
                Config::espColor.x,
                Config::espColor.y,
                Config::espColor.z,
                Config::espColor.w
            };

            j["Night"] = Config::Night;
            j["NightColor"] = {
                Config::NightColor.x,
                Config::NightColor.y,
                Config::NightColor.z,
                Config::NightColor.w
            };

            j["enemyChamsInvisible"] = Config::enemyChamsInvisible;
            j["enemyChams"] = Config::enemyChams;
            j["teamChams"] = Config::teamChams;
            j["teamChamsInvisible"] = Config::teamChamsInvisible;
            j["colVisualChams"] = {
                Config::colVisualChams.x,
                Config::colVisualChams.y,
                Config::colVisualChams.z,
                Config::colVisualChams.w
            };
            j["colVisualChamsIgnoreZ"] = {
                Config::colVisualChamsIgnoreZ.x,
                Config::colVisualChamsIgnoreZ.y,
                Config::colVisualChamsIgnoreZ.z,
                Config::colVisualChamsIgnoreZ.w
            };
            j["teamcolVisualChamsIgnoreZ"] = {
                Config::teamcolVisualChamsIgnoreZ.x,
                Config::teamcolVisualChamsIgnoreZ.y,
                Config::teamcolVisualChamsIgnoreZ.z,
                Config::teamcolVisualChamsIgnoreZ.w
            };
            j["teamcolVisualChams"] = {
                Config::teamcolVisualChams.x,
                Config::teamcolVisualChams.y,
                Config::teamcolVisualChams.z,
                Config::teamcolVisualChams.w
            };

            auto filePath = GetConfigPath(configName);
            std::ofstream ofs(filePath);
            if (ofs.is_open())
            {
                ofs << j.dump(4);
                ofs.close();
            }
        }

        static void Load(const std::string& configName)
        {
            auto filePath = GetConfigPath(configName);
            if (!std::filesystem::exists(filePath))
                return;

            std::ifstream ifs(filePath);
            if (!ifs.is_open())
                return;

            nlohmann::json j;
            ifs >> j;

            Config::esp = j.value("esp", false);
            Config::showHealth = j.value("showHealth", false);
            Config::teamCheck = j.value("teamCheck", false);
            Config::espFill = j.value("espFill", false);
            Config::espThickness = j.value("espThickness", 1.0f);
            Config::espFillOpacity = j.value("espFillOpacity", 0.5f);

            if (j.contains("espColor") && j["espColor"].is_array() && j["espColor"].size() == 4)
            {
                auto arr = j["espColor"];
                Config::espColor.x = arr[0].get<float>();
                Config::espColor.y = arr[1].get<float>();
                Config::espColor.z = arr[2].get<float>();
                Config::espColor.w = arr[3].get<float>();
            }

            Config::Night = j.value("Night", false);
            if (j.contains("NightColor") && j["NightColor"].is_array() && j["NightColor"].size() == 4)
            {
                auto arr = j["NightColor"];
                Config::NightColor.x = arr[0].get<float>();
                Config::NightColor.y = arr[1].get<float>();
                Config::NightColor.z = arr[2].get<float>();
                Config::NightColor.w = arr[3].get<float>();
            }

            Config::enemyChamsInvisible = j.value("enemyChamsInvisible", false);
            Config::enemyChams = j.value("enemyChams", false);
            Config::teamChams = j.value("teamChams", false);
            Config::teamChamsInvisible = j.value("teamChamsInvisible", false);

            if (j.contains("colVisualChams") && j["colVisualChams"].is_array() && j["colVisualChams"].size() == 4)
            {
                auto arr = j["colVisualChams"];
                Config::colVisualChams.x = arr[0].get<float>();
                Config::colVisualChams.y = arr[1].get<float>();
                Config::colVisualChams.z = arr[2].get<float>();
                Config::colVisualChams.w = arr[3].get<float>();
            }

            if (j.contains("colVisualChamsIgnoreZ") && j["colVisualChamsIgnoreZ"].is_array() && j["colVisualChamsIgnoreZ"].size() == 4)
            {
                auto arr = j["colVisualChamsIgnoreZ"];
                Config::colVisualChamsIgnoreZ.x = arr[0].get<float>();
                Config::colVisualChamsIgnoreZ.y = arr[1].get<float>();
                Config::colVisualChamsIgnoreZ.z = arr[2].get<float>();
                Config::colVisualChamsIgnoreZ.w = arr[3].get<float>();
            }

            if (j.contains("teamcolVisualChamsIgnoreZ") && j["teamcolVisualChamsIgnoreZ"].is_array() && j["teamcolVisualChamsIgnoreZ"].size() == 4)
            {
                auto arr = j["teamcolVisualChamsIgnoreZ"];
                Config::teamcolVisualChamsIgnoreZ.x = arr[0].get<float>();
                Config::teamcolVisualChamsIgnoreZ.y = arr[1].get<float>();
                Config::teamcolVisualChamsIgnoreZ.z = arr[2].get<float>();
                Config::teamcolVisualChamsIgnoreZ.w = arr[3].get<float>();
            }

            if (j.contains("teamcolVisualChams") && j["teamcolVisualChams"].is_array() && j["teamcolVisualChams"].size() == 4)
            {
                auto arr = j["teamcolVisualChams"];
                Config::teamcolVisualChams.x = arr[0].get<float>();
                Config::teamcolVisualChams.y = arr[1].get<float>();
                Config::teamcolVisualChams.z = arr[2].get<float>();
                Config::teamcolVisualChams.w = arr[3].get<float>();
            }

            ifs.close();
        }

        static void Remove(const std::string& configName)
        {
            auto filePath = GetConfigPath(configName);
            if (std::filesystem::exists(filePath))
            {
                std::error_code ec;
                std::filesystem::remove(filePath, ec);
            }
        }
    };
}
