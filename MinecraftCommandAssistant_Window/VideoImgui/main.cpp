
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


//��ǰ���ú�������
// ===============================================��������===============================================
#pragma region ��������
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
// ===============================================�ؼ�===============================================
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
	
	// �����Ƿ���ʾ�����ж�
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

		ImGui::Begin(u8"�ҵ����硪��ע��ʽ����������");
		ImGui::Text(u8"֧����Ϸ�汾:1.14.4+");

		if (ImGui::CollapsingHeader(u8"��������")) {
			if (ImGui::BeginTable("chickboxTable1",3))
			{
				ImGui::TableNextColumn(); ImGui::Checkbox(u8"��������", &show_basic_commands);
				ImGui::TableNextColumn(); ImGui::Checkbox(u8"��Ʒ����", &show_give);
				ImGui::TableNextColumn(); ImGui::Checkbox(u8"�������", &show_setblock);
				ImGui::TableNextColumn(); ImGui::Checkbox(u8"ʵ���ٻ�", &show_summon);
				ImGui::TableNextColumn(); ImGui::Checkbox(u8"�滻��Ʒ/����", &show_replaceitem);
				ImGui::TableNextColumn(); ImGui::Checkbox(u8"�Ʒְ�", &show_scoreboard);
				ImGui::TableNextColumn(); ImGui::Checkbox(u8"����", &show_team);
				ImGui::TableNextColumn(); ImGui::Checkbox(u8"����Ч��", &show_particle);
				ImGui::TableNextColumn(); ImGui::Checkbox(u8"ʵ��ִ��", &show_execute);
				ImGui::TableNextColumn(); ImGui::Checkbox(u8"ʵ����ɢ", &show_spreadplayers);
				ImGui::TableNextColumn(); ImGui::Checkbox(u8"����߽�", &show_worldborder);
				ImGui::TableNextColumn(); ImGui::Checkbox(u8"BOOS��", &show_bossbar);
				ImGui::EndTable();
			}
		}

		if (ImGui::CollapsingHeader(u8"JSON���")) {

		}

		ImGui::Separator();

		if (ImGui::CollapsingHeader(u8"����NBT��Ʒ/����")) {

		}

		if (ImGui::CollapsingHeader(u8"������Ʒ/����")) {

		}

		ImGui::Separator();

		if (ImGui::CollapsingHeader(u8"����NBTʵ��")) {

		}

		if (ImGui::CollapsingHeader(u8"����ʵ��")) {

		}

		ImGui::Separator();

		if (ImGui::CollapsingHeader(u8"�����Ϣ")) {
			ImGui::Text(u8"�йش���Ŀ:");
			ImGui::BulletText(u8"����Ŀ��zrydnoob����");
			ImGui::BulletText(u8"����Ŀʹ��ImGui��������ͨ��dllע��ֱ������Ϸ������");
			ImGui::BulletText(u8"�������� 2024/2/2��ʼ");
		}

		ImGui::End();

		ImGui::Begin(u8"�����д���");
		ImGui::Text(u8"�����������");
		ImGui::InputTextMultiline("##command", command,16384, ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 6));
		if (ImGui::Button(u8"����"))
		{
			clipboard << command;
		}
		ImGui::SameLine();
		if (ImGui::Button(u8"���"))
		{
			strcpy_s(command, "");
		}	

		ImGui::End();

		// �жϴ�����ʾ�߼�
		// ===============================================��������===============================================
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

// ===============================================��������===============================================
#pragma region ��������
// ���������
static void ShowBasicCommands() {
	ImGui::Begin(u8"��������");
	ImGui::Text(u8"��ͼ");
	if (ImGui::CollapsingHeader(u8"��Ϸģʽ")) {
		static int gamemode = 0;
		ImGui::RadioButton(u8"����ģʽ", &gamemode, 0); ImGui::SameLine();
		ImGui::RadioButton(u8"����ģʽ", &gamemode, 1); ImGui::SameLine();
		ImGui::RadioButton(u8"ð��ģʽ", &gamemode, 2); ImGui::SameLine();
		ImGui::RadioButton(u8"�Թ�ģʽ", &gamemode, 3); 
		static char player[128] = ""; PlayerChoose(u8"���ѡ����",player);
		if (ImGui::Button(u8"��������")) {
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
	if (ImGui::CollapsingHeader(u8"����")) {

	}
	if (ImGui::CollapsingHeader(u8"�Ѷ�")) {

	}
	if (ImGui::CollapsingHeader(u8"������")) {

	}
	ImGui::Separator();
	ImGui::Text(u8"���");
	if (ImGui::CollapsingHeader(u8"����")) {

	}
	if (ImGui::CollapsingHeader(u8"�ȼ�")) {

	}
	ImGui::Separator();
	ImGui::Text(u8"��Ϸ");
	if (ImGui::CollapsingHeader(u8"ʱ��")) {

	}
	if (ImGui::CollapsingHeader(u8"����")) {

	}
	ImGui::End();
}

// ��Ʒ����
static void ShowGive() {
	ImGui::Begin(u8"��Ʒ����");
	ImGui::End();
}


// �������
static void ShowSetBlock() {
	ImGui::Begin(u8"�������");
	ImGui::End();
}

// ʵ���ٻ�
static void ShowSummon() {
	ImGui::Begin(u8"ʵ���ٻ�");
	ImGui::End();
}

// �滻��Ʒ/����
static void ShowReplaceitem() {
	ImGui::Begin(u8"�滻��Ʒ/����");
	ImGui::End();
}

// �Ʒְ�
static void ShowScoreboard() {
	ImGui::Begin(u8"�Ʒְ�");
	ImGui::End();
}

// ����
static void ShowTeam() {
	ImGui::Begin(u8"����");
	ImGui::End();
}

// ����Ч��
static void ShowParticle() {
	ImGui::Begin(u8"����Ч��");
	ImGui::End();
}

// ʵ��ִ��
static void ShowExecute() {
	ImGui::Begin(u8"ʵ��ִ��");
	ImGui::End();
}

// ʵ����ɢ
static void ShowSpreadplayers() {
	ImGui::Begin(u8"ʵ����ɢ");
	ImGui::End();
}

// ����߽�
static void ShowWorldborder() {
	ImGui::Begin(u8"����߽�");
	ImGui::End();
}

// BOOS��
static void ShowBossBar() {
	ImGui::Begin(u8"BOOS��");
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
		ImGui::TextUnformatted(u8"���ѡ����:\n@a �������\n@s ����ִ����\n@p ��������\n@e ȫ��ʵ��\n@r ������\n@p[c=-1] ������Զ�����");
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}