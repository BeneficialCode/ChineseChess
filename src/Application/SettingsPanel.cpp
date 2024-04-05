#include "Application.h"

#include <imgui.h>

#include <glm/gtc/type_ptr.hpp>

void Application::RenderSettingsPanel(bool* show) {
    if (!*show)
        return;

    ImGuiColorEditFlags colourEditFlags = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaBar;

    ImGui::Begin("Settings", show);

    static int currentTheme;
    static const char* themes[] = { "Dark", "Light" };

    if (ImGui::BeginTable("ColoursTable", 2, ImGuiTableFlags_SizingFixedSame)) {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Theme");
        ImGui::TableNextColumn();
        if (ImGui::Combo("##Theme", &currentTheme, themes, sizeof(themes) / sizeof(const char*))) {
            if (currentTheme == 0)
                ImGui::StyleColorsDark();
            else
                ImGui::StyleColorsLight();
        }

        ImGui::EndTable();
    }

    ImGui::End();
}