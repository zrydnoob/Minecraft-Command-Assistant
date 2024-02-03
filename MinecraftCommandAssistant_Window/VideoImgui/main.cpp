
#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#pragma comment(lib,"../API/GLFW/glfw3.lib")
#pragma comment(lib,"../API/GLEW/glew32s.lib")
#pragma comment(lib,"Opengl32.lib")
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <clipboardxx.hpp>


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GUI.h"

GLFWwindow* Windows;


//提前调用函数声明
// ===============================================基础命令===============================================
#pragma region 基础命令
static void ShowBasicCommands();
static void ShowGive();
static void ShowSetBlock();
static void ShowSummon();
static void ShowReplaceitem();
static void ShowScoreboard();
static void ShowTeam();
static void ShowParticle();
static void ShowExecute();
static void ShowSpreadplayers();
static void ShowWorldborder();
static void ShowBossBar();
// ===============================================控价===============================================
static void PlayerChoose(const char* label, char* player);
#pragma endregion


static char command[1024*16];


int main()
{
	clipboardxx::clipboard clipboard;


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

	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	

	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();

#pragma region Styles
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

#pragma endregion

	ImGui_ImplGlfw_InitForOpenGL(Windows, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	/*te = new TextEditor();
	te->SetLanguageDefinition(TextEditor::LanguageDefinition::C());*/
	
	// 窗口是否显示布尔判断
#pragma region WindowBool
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
#pragma endregion

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

		ImGui::Begin(u8"命令行窗口");
		ImGui::Text(u8"命令输出窗口");
		ImGui::InputTextMultiline("##command", command,16384, ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 6));
		if (ImGui::Button(u8"复制"))
		{
			clipboard << command;
		}
		ImGui::SameLine();
		if (ImGui::Button(u8"清空"))
		{
			strcpy_s(command, "");
		}	

		ImGui::End();

		// 判断窗口显示逻辑
		// ===============================================基础命令===============================================
		if (show_basic_commands) { ShowBasicCommands(); }
		if (show_give) { ShowGive(); }
		if (show_setblock) { ShowSetBlock(); }
		if (show_summon) { ShowSummon(); }
		if (show_replaceitem) { ShowReplaceitem(); }
		if (show_scoreboard) { ShowScoreboard(); }
		if (show_team) { ShowTeam(); }
		if (show_particle) { ShowParticle(); }
		if (show_execute) { ShowExecute(); }
		if (show_spreadplayers) { ShowSpreadplayers(); }
		if (show_worldborder) { ShowWorldborder(); }
		if (show_bossbar) { ShowBossBar(); }



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

// ===============================================基础命令===============================================
#pragma region 基础命令
// 基础命令窗口
static void ShowBasicCommands() {
	ImGui::Begin(u8"基础命令");
	ImGui::Text(u8"地图");
	if (ImGui::CollapsingHeader(u8"游戏模式")) {
		static int gamemode = 0;
		ImGui::RadioButton(u8"生存模式", &gamemode, 0); ImGui::SameLine();
		ImGui::RadioButton(u8"创造模式", &gamemode, 1); ImGui::SameLine();
		ImGui::RadioButton(u8"冒险模式", &gamemode, 2); ImGui::SameLine();
		ImGui::RadioButton(u8"旁观模式", &gamemode, 3); 
		static char player[128] = ""; PlayerChoose(u8"玩家选择器",player);
		if (ImGui::Button(u8"生成命令")) {
			std::string gamemodeCommand;
			std::ostringstream buffer;
			switch (gamemode)
			{
			case 0:
				gamemodeCommand = "survival";
				break;
			case 1:
				gamemodeCommand = "creative";
				break;
			case 2:
				gamemodeCommand = "adventure";
				break;
			case 3:
				gamemodeCommand = "spectator";
				break;
			} 
			buffer << "/gamemode " << player << " " << gamemodeCommand;
			strcpy_s(command, buffer.str().data());
		}
	}
	if (ImGui::CollapsingHeader(u8"规则")) {

	}
	if (ImGui::CollapsingHeader(u8"难度")) {

	}
	if (ImGui::CollapsingHeader(u8"出生点")) {

	}
	ImGui::Separator();
	ImGui::Text(u8"玩家");
	if (ImGui::CollapsingHeader(u8"传送")) {

	}
	if (ImGui::CollapsingHeader(u8"等级")) {

	}
	ImGui::Separator();
	ImGui::Text(u8"游戏");
	if (ImGui::CollapsingHeader(u8"时间")) {

	}
	if (ImGui::CollapsingHeader(u8"天气")) {

	}
	ImGui::End();
}

// 物品给予
static void ShowGive() {
	ImGui::Begin(u8"物品给予");
	ImGui::End();
}


// 方块放置
static void ShowSetBlock() {
	ImGui::Begin(u8"方块放置");
	ImGui::End();
}

// 实体召唤
static void ShowSummon() {
	ImGui::Begin(u8"实体召唤");
	ImGui::End();
}

// 替换物品/方块
static void ShowReplaceitem() {
	ImGui::Begin(u8"替换物品/方块");
	ImGui::End();
}

// 计分板
static void ShowScoreboard() {
	ImGui::Begin(u8"计分板");
	ImGui::End();
}

// 队伍
static void ShowTeam() {
	ImGui::Begin(u8"队伍");
	ImGui::End();
}

// 粒子效果
static void ShowParticle() {
	ImGui::Begin(u8"粒子效果");
	ImGui::End();
}

// 实体执行
static void ShowExecute() {
	ImGui::Begin(u8"实体执行");
	ImGui::End();
}

// 实体扩散
static void ShowSpreadplayers() {
	ImGui::Begin(u8"实体扩散");
	ImGui::End();
}

// 世界边界
static void ShowWorldborder() {
	ImGui::Begin(u8"世界边界");
	ImGui::End();
}

// BOOS栏
static void ShowBossBar() {
	ImGui::Begin(u8"BOOS栏");
	ImGui::End();
}

#pragma endregion


static void PlayerChoose(const char* label,char* player) {
	ImGui::InputText(label, player, ((int)(sizeof(player) / sizeof(*(player))))); ImGui::SameLine();
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(u8"玩家选择器:\n@a 所有玩家\n@s 命令执行者\n@p 最近的玩家\n@e 全部实体\n@r 随机玩家\n@p[c=-1] 距离最远的玩家");
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}