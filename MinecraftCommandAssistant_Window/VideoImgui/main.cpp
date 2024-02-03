
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#pragma comment(lib,"../API/GLFW/glfw3.lib")
#pragma comment(lib,"../API/GLEW/glew32s.lib")
#pragma comment(lib,"Opengl32.lib")
#include <iostream>
#include <string>


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GUI.h"

GLFWwindow* Windows;


//提前调用函数声明
static void ShowBasicCommands();

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Windows = glfwCreateWindow(900, 800,"HalfPeople-Imgui",NULL,NULL);

	glfwMakeContextCurrent(Windows);
	glfwSwapInterval(0);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext(NULL);
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.Fonts->AddFontFromFileTTF("tgt.ttf", 18, NULL, io.Fonts->GetGlyphRangesChineseFull());

	

	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();

	ImVec4* colors = style.Colors;
	colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.16f, 0.17f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.37f, 0.36f, 0.36f, 102.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.10f, 0.10f, 0.10f, 171.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.20f, 0.20f, 0.20f, 255.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.22f, 0.22f, 0.22f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.45f, 0.45f, 0.45f, 0.31f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.55f, 0.55f, 0.55f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.20f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.46f, 0.46f, 0.46f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.17f, 0.17f, 0.17f, 0.95f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.50f, 0.50f, 0.50f, 0.78f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.45f, 0.45f, 0.45f, 0.80f);
	colors[ImGuiCol_TabActive] = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
	colors[ImGuiCol_DockingPreview] = ImVec4(0.51f, 0.51f, 0.51f, 0.70f);
	colors[ImGuiCol_Tab] = ImVec4(0.21f, 0.21f, 0.21f, 0.86f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.15f, 0.15f, 0.15f, 0.97f);
	colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.40f, 0.13f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.45f, 1.00f, 0.85f, 0.35f);


	style.WindowRounding = 4;
	style.FrameRounding = 4;
	style.GrabRounding = 3;
	style.ScrollbarSize = 7;
	style.ScrollbarRounding = 0;


	ImGui_ImplGlfw_InitForOpenGL(Windows, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	/*te = new TextEditor();
	te->SetLanguageDefinition(TextEditor::LanguageDefinition::C());*/
	
	// 窗口是否显示布尔判断
	static bool show_basic_commands = false;
	static bool show_give = false;
	static bool show_setblock = false;
	static bool show_summon = false;
	static bool show_replaceitem = false;
	static bool show_scoreboard = false;
	static bool show_team = false;
	static bool show_particle = false;
	static bool show_execute = false;
	static bool show_spreadplayers = false;
	static bool show_worldborder = false;
	static bool show_bossbar = false;


	while (!glfwWindowShouldClose(Windows))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		//ImGui::DockSpaceOverViewport();

		//DrawGUI();

		ImGui::ShowDemoWindow();

		ImGui::Begin(u8"我的世界——注入式命令生成器");
		ImGui::Text(u8"支持游戏版本:1.14.4+");

		if (ImGui::CollapsingHeader(u8"基础功能")) {
			if (ImGui::BeginTable("chickboxTable1",3))
			{
				ImGui::TableNextColumn(); ImGui::Checkbox(u8"基础命令", &show_basic_commands);
				ImGui::TableNextColumn(); ImGui::Checkbox(u8"物品给予", &show_give);
				ImGui::TableNextColumn(); ImGui::Checkbox(u8"方块放置", &show_setblock);
				ImGui::TableNextColumn(); ImGui::Checkbox(u8"实体召唤", &show_summon);
				ImGui::TableNextColumn(); ImGui::Checkbox(u8"替换物品/方块", &show_replaceitem);
				ImGui::TableNextColumn(); ImGui::Checkbox(u8"计分板", &show_scoreboard);
				ImGui::TableNextColumn(); ImGui::Checkbox(u8"队伍", &show_team);
				ImGui::TableNextColumn(); ImGui::Checkbox(u8"粒子效果", &show_particle);
				ImGui::TableNextColumn(); ImGui::Checkbox(u8"实体执行", &show_execute);
				ImGui::TableNextColumn(); ImGui::Checkbox(u8"实体扩散", &show_spreadplayers);
				ImGui::TableNextColumn(); ImGui::Checkbox(u8"世界边界", &show_worldborder);
				ImGui::TableNextColumn(); ImGui::Checkbox(u8"BOOS栏", &show_bossbar);
				ImGui::EndTable();
			}
		}

		if (ImGui::CollapsingHeader(u8"JSON相关")) {

		}

		ImGui::Separator();

		if (ImGui::CollapsingHeader(u8"特殊NBT物品/方块")) {

		}

		if (ImGui::CollapsingHeader(u8"复合物品/方块")) {

		}

		ImGui::Separator();

		if (ImGui::CollapsingHeader(u8"特殊NBT实体")) {

		}

		if (ImGui::CollapsingHeader(u8"复合实体")) {

		}

		ImGui::Separator();

		if (ImGui::CollapsingHeader(u8"相关信息")) {
			ImGui::Text(u8"有关此项目:");
			ImGui::BulletText(u8"本项目由zrydnoob开发");
			ImGui::BulletText(u8"本项目使用ImGui开发，并通过dll注入直接在游戏中运行");
			ImGui::BulletText(u8"开发日期 2024/2/2开始");
		}

		ImGui::End();

		// 判断窗口显示逻辑
		// ===============================================基础命令===============================================
		if (show_basic_commands) { ShowBasicCommands(); }
		if (show_give) { ShowBasicCommands(); }
		if (show_setblock) { ShowBasicCommands(); }
		if (show_summon) { ShowBasicCommands(); }
		if (show_replaceitem) { ShowBasicCommands(); }
		if (show_scoreboard) { ShowBasicCommands(); }
		if (show_team) { ShowBasicCommands(); }
		if (show_particle) { ShowBasicCommands(); }
		if (show_execute) { ShowBasicCommands(); }
		if (show_spreadplayers) { ShowBasicCommands(); }
		if (show_worldborder) { ShowBasicCommands(); }
		if (show_bossbar) { ShowBasicCommands(); }



		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		

		/*if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}*/

		glfwSwapBuffers(Windows);
		glfwPollEvents();
	}
}

// 基础命令窗口
static void ShowBasicCommands() {
	ImGui::Begin(u8"基础命令");
	ImGui::End();
}