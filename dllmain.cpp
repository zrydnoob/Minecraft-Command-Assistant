// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include<iostream>
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include "ClipboardXX/include/clipboardxx.hpp"


#include "opengl_imgui/include/imgui_opengl_hook.h"

#pragma comment(lib, "libMinHook.x64.lib")
#pragma comment(lib, "opengl_imgui_x64.lib")
#pragma comment(lib, "opengl32.lib")

bool demo;
int number = 0;

static char command[1024 * 16];

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
// ===============================================控件===============================================
static void PlayerChoose(const char* label, char* player);
static void HelpMarker(const char* desc);
#pragma endregion

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

void ren() {
	clipboardxx::clipboard clipboard;
	ImGui::Begin(u8"我的世界——注入式命令生成器");
	ImGui::Text(u8"支持游戏版本:1.14.4+");

	if (ImGui::CollapsingHeader(u8"基础功能")) {
		if (ImGui::BeginTable("chickboxTable1", 3))
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
	ImGui::InputTextMultiline("##command", command, 16384, ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 6));
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
}

void config(ImGuiIO& io) {
    ImGui::StyleColorsClassic();
	//TODO
    //io.Fonts->AddFontFromFileTTF("F:\\work\\c++\\Minecraft-Command-Assistant\\alibaba.ttf", 18, NULL,io.Fonts->GetGlyphRangesChineseFull());

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

}

void run() {
    SetConfig(config);
    initHook();
    SetGui(ren , VK_INSERT);
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
		static char player[1204 * 16] = ""; PlayerChoose(u8"更改游戏模式玩家", player);
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
			buffer << "/gamemode " << gamemodeCommand << " " << player;
			strcpy_s(command, buffer.str().data());
		}
	}
	if (ImGui::CollapsingHeader(u8"规则(仅支持bool类型规则)")) {
		static int is_enable = 0;
		ImGui::RadioButton(u8"禁用", &is_enable, 0); ImGui::SameLine();
		ImGui::RadioButton(u8"启用", &is_enable, 1);
		const char* gamerules[] = { "announceAdvancements", "blockExplosionDropDecay", "commandBlockOutput",
			"disableElytraMovementCheck", "disableRaids", "doDaylightCycle", "doEntityDrops",
			"doFireTick", "doImmediateRespawn","doInsomnia","doLimitedCrafting","doMobLoot","doMobSpawning","doPatrolSpawning","doTileDrops",
			"doTraderSpawning","doVinesSpread","doWardenSpawning","doWeatherCycle","drowningDamage","enderPearlsVanishOnDeath",
			"fallDamage","fireDamage","forgiveDeadPlayers","freezeDamage","globalSoundEvents","keepInventory",
			"lavaSourceConversion","logAdminCommands","mobExplosionDropDecay","mobGriefing",
			"naturalRegeneration","projectilesCanBreakBlocks","reducedDebugInfo","sendCommandFeedback",
			"showDeathMessages","showTags","spectatorsGenerateChunks","tntExplosionDropDecay",
			"universalAnger","waterSourceConversion" };
		static int gamerulevaluse = 0;
		ImGui::Combo(u8"游戏规则", &gamerulevaluse, gamerules, IM_ARRAYSIZE(gamerules)); ImGui::SameLine();
		HelpMarker(u8"announceAdvancements	是否在聊天框中公告玩家进度的达成\
			\nblockExplosionDropDecay	由方块源（除TNT）爆炸炸毁的方块是否会有概率不掉落\
			\ncommandBlockOutput	命令方块执行命令时是否在聊天框中向管理员显示\
			\ndisableElytraMovementCheck	是否让服务器停止检查使用鞘翅玩家的移动速度\
			\ndisableRaids	是否禁用袭击\
			\ndoDaylightCycle	是否进行昼夜更替和月相变化\
			\ndoEntityDrops	非生物实体是否掉落物品\
			\ndoFireTick	火是否蔓延及自然熄灭\
			\ndoImmediateRespawn	玩家死亡时是否不显示死亡界面直接重生\
			\ndoInsomnia	幻翼是否在夜晚生成\
			\ndoLimitedCrafting	玩家的合成配方是否需要解锁才能使用\
			\ndoMobLoot	生物在死亡时是否掉落物品\
			\ndoMobSpawning	生物是否自然生成。不影响刷怪笼\
			\ndoPatrolSpawning	控制灾厄巡逻队的生成\
			\ndoTileDrops	方块被破坏时是否掉落物品\
			\ndoTraderSpawning	控制流浪商人的生成\
			\ndoVinesSpread	决定藤蔓是否会向周围扩散，不影响洞穴藤蔓、缠怨藤和垂泪藤\
			\ndoWardenSpawning	监守者是否生成\
			\ndoWeatherCycle	天气是否变化\
			\ndrowningDamage	玩家是否承受窒息伤害\
			\nenderPearlsVanishOnDeath	被掷出的末影珍珠是否会在掷出它的玩家死亡后消失\
			\nfallDamage	玩家是否承受跌落伤害\
			\nfireDamage	玩家是否承受火焰伤害\
			\nforgiveDeadPlayers	当被激怒的条件敌对生物的目标玩家死亡时，该生物是否恢复未激怒状态\
			\nfreezeDamage	玩家是否承受冰冻伤害\
			\nglobalSoundEvents	玩家是否能听到可无视距离播放给全部玩家的特定游戏事件音效\
			\nkeepInventory	玩家死亡后是否保留物品栏物品、经验（死亡时物品不掉落、经验不清空）\
			\nlavaSourceConversion	流动的熔岩是否可产生熔岩源\
			\nlogAdminCommands	是否在服务器日志中记录管理员使用过的命令\
			\nmobExplosionDropDecay	由生物源爆炸炸毁的方块是否会有概率不掉落\
			\nmobGriefing	生物是否能够进行破坏性行为\
			\nnaturalRegeneration	玩家是否能在饥饿值足够时自然恢复生命值\
			\nreducedDebugInfo	调试屏幕是否简化而非显示详细信息\
			\nsendCommandFeedback	玩家执行命令的返回信息是否在聊天框中显示。同时影响命令方块是否保存命令输出文本\
			\nshowDeathMessages	是否在聊天框中显示玩家的死亡信息\
			\nspectatorsGenerateChunks	是否允许旁观模式的玩家生成区块\
			\ntntExplosionDropDecay	由TNT爆炸炸毁的方块是否会有概率不掉落\
			\nuniversalAnger	被激怒的条件敌对生物是否攻击附近任何玩家\
			\nwaterSourceConversion	流动的水是否可产生水源");
		if (ImGui::Button(u8"生成命令"))
		{
			std::string statue;
			std::ostringstream buffer;
			if (is_enable == 0)
			{
				statue = "false";
			}
			else {
				statue = "true";
			}
			buffer << "/gamerule " << gamerules[gamerulevaluse] << " " << statue;
			strcpy_s(command, buffer.str().data());
		}

	}
	if (ImGui::CollapsingHeader(u8"难度")) {
		static int difficulty = 0;
		ImGui::RadioButton(u8"和平", &difficulty, 0); ImGui::SameLine();
		ImGui::RadioButton(u8"简单", &difficulty, 1); ImGui::SameLine();
		ImGui::RadioButton(u8"普通", &difficulty, 2); ImGui::SameLine();
		ImGui::RadioButton(u8"困难", &difficulty, 3);
		if (ImGui::Button(u8"生成命令"))
		{
			std::string difficultyCommand;
			switch (difficulty)
			{
			case 0:
				difficultyCommand = "peaceful";
				break;
			case 1:
				difficultyCommand = "easy";
				break;
			case 2:
				difficultyCommand = "normal";
				break;
			case 3:
				difficultyCommand = "hard";
				break;
			}
			std::ostringstream buffer;
			buffer << "/difficulty " << difficultyCommand;
			strcpy_s(command, buffer.str().data());
		}
	}
	if (ImGui::CollapsingHeader(u8"出生点")) {
		static int x;
		static int y;
		static int z;
		ImGui::InputInt("x", &x);
		ImGui::InputInt("y", &y);
		ImGui::InputInt("z", &z);
		static char player[1204 * 16] = ""; PlayerChoose(u8"设置出生点玩家", player);
		if (ImGui::Button(u8"生成命令")) {
			std::ostringstream buffer;
			buffer << "/spawnpoint " << player << " " << x << " " << y << " " << z;
			strcpy_s(command, buffer.str().data());
		}
	}
	ImGui::Separator();
	ImGui::Text(u8"玩家");
	if (ImGui::CollapsingHeader(u8"传送")) {
		if (ImGui::TreeNode(u8"传送到玩家"))
		{
			static char p1[1204 * 16] = ""; PlayerChoose(u8"要传送的玩家", p1);
			static char p2[1204 * 16] = ""; PlayerChoose(u8"传送到的玩家", p2);
			if (ImGui::Button(u8"生成命令")) {
				std::ostringstream buffer;
				buffer << "/tp " << p1 << " " << p2;
				strcpy_s(command, buffer.str().data());
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode(u8"传送到坐标"))
		{
			static int x;
			static int y;
			static int z;
			ImGui::InputInt("x", &x);
			ImGui::InputInt("y", &y);
			ImGui::InputInt("z", &z);
			static char player[1204 * 16] = ""; PlayerChoose(u8"要传送的玩家##1", player);
			if (ImGui::Button(u8"生成命令")) {
				std::ostringstream buffer;
				buffer << "/tp " << player << " " << x << " " << y << " " << z;
				strcpy_s(command, buffer.str().data());
			}
			ImGui::TreePop();
		}
	}


	if (ImGui::CollapsingHeader(u8"等级")) {
		static int is_leavels = 0;
		static int value;
		ImGui::RadioButton(u8"经验", &is_leavels, 0); ImGui::SameLine();
		ImGui::RadioButton(u8"等级##1", &is_leavels, 1);
		static char player[1204 * 16] = ""; PlayerChoose(u8"增加经验值玩家", player);
		ImGui::InputInt(u8"值", &value);
		if (ImGui::Button(u8"生成命令")) {
			std::ostringstream buffer;
			if (is_leavels == 0)
			{
				buffer << "/xp add " << player << " " << value << " points";
			}
			else
			{
				buffer << "/xp add " << player << " " << value << " leavels";
			}
			strcpy_s(command, buffer.str().data());
		}
	}
	ImGui::Separator();
	ImGui::Text(u8"游戏");
	if (ImGui::CollapsingHeader(u8"时间")) {
		static int time;
		ImGui::InputInt(u8"设置时间 (游戏刻)", &time);
		if (ImGui::Button(u8"生成命令")) {
			std::ostringstream buffer;
			buffer << "/time set " << time;
			strcpy_s(command, buffer.str().data());
		}
	}
	if (ImGui::CollapsingHeader(u8"天气")) {
		static int weather = 0;
		static int time = 100;
		ImGui::RadioButton(u8"晴天", &weather, 0); ImGui::SameLine();
		ImGui::RadioButton(u8"雨天", &weather, 1); ImGui::SameLine();
		ImGui::RadioButton(u8"暴雨", &weather, 2);
		ImGui::InputInt(u8"持续时间", &time);
		if (ImGui::Button(u8"生成命令")) {
			std::ostringstream buffer;
			std::string weatherCommand;
			switch (weather)
			{
			case 0:
				weatherCommand = "clear";
				break;
			case 1:
				weatherCommand = "rain";
				break;
			case 2:
				weatherCommand = "thunder";
				break;
			}
			buffer << "/weather " << weatherCommand << " " << time;
			strcpy_s(command, buffer.str().data());
		}
	}
	ImGui::Separator();
	ImGui::Text(u8"注意：为防止页面过长,请勿展开多个标签页,否则无法生成命令");
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


static void PlayerChoose(const char* label, char* player) {
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

static void HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        run();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

