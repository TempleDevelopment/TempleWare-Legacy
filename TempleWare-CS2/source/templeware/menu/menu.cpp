#include "menu.h"
#include "../config/config.h"

#include <iostream>
#include <vector>
#include "../config/configmanager.h"

void ApplyImGuiTheme() {
    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.09f, 0.09f, 1.0f);
    colors[ImGuiCol_Border] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.0f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.24f, 0.24f, 1.0f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.24f, 0.24f, 0.24f, 1.0f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.09f, 0.09f, 1.0f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.09f, 0.09f, 0.09f, 1.0f);

    colors[ImGuiCol_Button] = ImVec4(0.60f, 0.30f, 0.80f, 1.0f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.70f, 0.40f, 0.90f, 1.0f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.50f, 0.20f, 0.70f, 1.0f);

    colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.50f, 1.00f, 1.0f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.60f, 0.30f, 0.80f, 1.0f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.70f, 0.40f, 0.90f, 1.0f);

    colors[ImGuiCol_Header] = ImVec4(0.60f, 0.30f, 0.80f, 1.0f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.70f, 0.40f, 0.90f, 1.0f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.50f, 0.20f, 0.70f, 1.0f);

    colors[ImGuiCol_Separator] = ImVec4(0.50f, 0.20f, 0.70f, 1.0f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.60f, 0.30f, 0.80f, 1.0f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.70f, 0.40f, 0.90f, 1.0f);

    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

    style.WindowRounding = 0.0f;
    style.FrameRounding = 0.0f;
    style.ScrollbarRounding = 0.0f;
    style.GrabRounding = 0.0f;

    style.ItemSpacing = ImVec2(10, 5);
    style.FramePadding = ImVec2(5, 5);
}

Menu::Menu() {
    activeTab = 0;
    showMenu = true;
}

void Menu::init(HWND& window, ID3D11Device* pDevice, ID3D11DeviceContext* pContext, ID3D11RenderTargetView* mainRenderTargetView) {
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(pDevice, pContext);

    ApplyImGuiTheme();

    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arial.ttf", 16.0f);

    std::cout << "initialized menu\n";
}

void Menu::render() {
    if (showMenu) {
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar;

        ImGui::SetNextWindowSize(ImVec2(500, 300), ImGuiCond_Once);
        ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_Once);

        ImGui::Begin("TempleWare | Internal", nullptr, window_flags);

        {
            float windowWidth = ImGui::GetWindowWidth();
            float leftTextWidth = ImGui::CalcTextSize("TempleWare - Internal").x;
            float rightTextWidth = ImGui::CalcTextSize("templecheats.xyz").x;

            ImGui::Text("TempleWare - Internal");

            ImGui::SameLine(windowWidth - rightTextWidth - 10);
            ImGui::Text("templecheats.xyz");
        }

        ImGui::Separator();
        ImGui::Spacing();

        {

            ImVec2 buttonSize(80, 0);

            if (ImGui::Button("Aim", buttonSize))       activeTab = 0; ImGui::SameLine();
            if (ImGui::Button("Visuals", buttonSize))   activeTab = 1; ImGui::SameLine();
            if (ImGui::Button("Misc", buttonSize))      activeTab = 2; ImGui::SameLine();
            if (ImGui::Button("Config", buttonSize))    activeTab = 3;
        }

        ImGui::Separator();
        ImGui::Spacing();

        ImGui::BeginChild("Main Content", ImVec2(0, 0), true);
        switch (activeTab) {
        case 0:
            ImGui::Text("Aim");
            ImGui::Separator();

            break;

        case 1:
            ImGui::Text("Visuals");
            ImGui::Separator();

            if (ImGui::CollapsingHeader("ESP")) {
                ImGui::Checkbox("Box", &Config::esp);
                ImGui::ColorEdit4("Color", (float*)&Config::espColor);
                ImGui::SliderFloat("Thickness", &Config::espThickness, 1.0f, 5.0f);
                ImGui::Checkbox("TeamCheck", &Config::teamCheck);
                ImGui::Checkbox("BoxFill", &Config::espFill);
                if (Config::espFill) {
                    ImGui::SliderFloat("FillOpacity", &Config::espFillOpacity, 0.0f, 1.0f);
                }
                ImGui::Checkbox("Health", &Config::showHealth);
            }

            ImGui::Separator();

            if (ImGui::CollapsingHeader("Chams")) {
                ImGui::Checkbox("Chams", &Config::enemyChams);
                ImGui::Checkbox("Chams-XQZ", &Config::enemyChamsInvisible);

                if (Config::enemyChams) {
                    ImGui::ColorEdit4("ColorVisible", (float*)&Config::colVisualChamsIgnoreZ);
                }

                if (Config::enemyChamsInvisible) {
                    ImGui::ColorEdit4("Color-XQZ", (float*)&Config::colVisualChams);
                }
            }

            ImGui::Separator();

            break;

        case 2:
            ImGui::Text("Misc");
            ImGui::Separator();
            ImGui::Checkbox("NightMode", &Config::Night);
            if (Config::Night)
                ImGui::ColorEdit4("Color", (float*)&Config::NightColor);

            break;

        case 3:
            ImGui::Text("Config");
            ImGui::Separator();
            static char configName[128] = "";
            static std::vector<std::string> configList = internal_config::ConfigManager::ListConfigs();
            static int selectedConfigIndex = -1;

            ImGui::InputText("Config Name", configName, IM_ARRAYSIZE(configName));

            if (ImGui::Button("Refresh Config List"))
            {
                configList = internal_config::ConfigManager::ListConfigs();
            }
            ImGui::SameLine();
            if (ImGui::Button("Load"))
            {
                internal_config::ConfigManager::Load(configName);
            }
            ImGui::SameLine();
            if (ImGui::Button("Save"))
            {
                internal_config::ConfigManager::Save(configName);
                configList = internal_config::ConfigManager::ListConfigs();
            }
            ImGui::SameLine();
            if (ImGui::Button("Delete"))
            {
                internal_config::ConfigManager::Remove(configName);
                configList = internal_config::ConfigManager::ListConfigs();
            }

            ImGui::Separator();
            ImGui::Text("Saved Configs:");
            for (int i = 0; i < static_cast<int>(configList.size()); i++)
            {
                if (ImGui::Selectable(configList[i].c_str(), selectedConfigIndex == i))
                {
                    selectedConfigIndex = i;

                    strncpy_s(configName, sizeof(configName), configList[i].c_str(), _TRUNCATE);
                }
            }
            break;
        }
        ImGui::EndChild();

        ImGui::End();
    }
}

void Menu::toggleMenu() {
    showMenu = !showMenu;
}
