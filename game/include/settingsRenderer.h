#pragma once

#include "rlImGui.h"
#include "imgui.h"
#include "settings.h"

inline void renderSettingsUI(Settings& settings) {
	// Messing with ImGui
	rlImGuiBegin();
		ImGuiIO& io = ImGui::GetIO(); // Get the screen dimensions
		ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x, 0.0f), ImGuiCond_Always, ImVec2(1.0f, 0.0f)); // Puts it in the top right
		ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize); // Autosizes it with flag
		ImGui::SliderInt("Player Hp", &settings.getPlayerHp(), 0, 100);
		ImGui::Text("FPS: %i", GetFPS());
		ImGui::End();
	rlImGuiEnd();
}