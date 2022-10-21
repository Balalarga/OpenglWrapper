#include "ImGuiSystem.h"

#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "System/OpenGL/OpenglSystem.h"
#include "System/WindowSystem/WindowSystem.h"
#include "Utils/Macroses.h"


ImGuiSystem::ImGuiSystem(const Params& params):
	ISystem(TOSTRING(ImGuiSystem)),
	_params(params)
{
}

bool ImGuiSystem::Init(bool bStatus)
{
	if (_params.windowSystem)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGui_ImplSDL2_InitForOpenGL(
			_params.windowSystem->GetWindow().GetInnerWindow(),
			_params.openglSystem->GetContext()
			);
		ImGui_ImplOpenGL3_Init(_params.glVersion);
		return true;
	}
	return false;
}

void ImGuiSystem::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}
