// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include<iostream>

#include "opengl_imgui/include/imgui_opengl_hook.h"

#pragma comment(lib, "libMinHook.x64.lib")
#pragma comment(lib, "opengl_imgui_x64.lib")
#pragma comment(lib, "opengl32.lib")

bool demo;
int number = 0;

void ren() {

    ImGui::ShowDemoWindow();
    ImGui::ShowDebugLogWindow();
    
    ImGui::Begin("Minecraft_HACK");
    ImGui::Text("ZRDClient Demo Dll Imgui.");
    ImGui::Checkbox("DemoCheckBot", &demo);
    if (ImGui::Button("DemoButton"))
    {
        number++;
    }
    ImGui::Text("counter = %d", number);
    ImGui::SameLine();
    ImGui::End();
}

void config(ImGuiIO& io) {
    ImGui::StyleColorsClassic();
    io.Fonts->AddFontFromFileTTF("F:\\work\\c++\\Minecraft_Gui\\alibaba.ttf", 18, NULL,io.Fonts->GetGlyphRangesChineseFull());

}

void run() {
    SetConfig(config);
    initHook();
    SetGui(ren , VK_INSERT);
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

