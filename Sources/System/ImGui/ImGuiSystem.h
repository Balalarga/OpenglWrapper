#pragma once

#include "System/ISystem.h"

namespace Oglw
{
class OpenglSystem;
class WindowSystem;

class ImGuiSystem: public ISystem
{
public:
	struct Params
	{
		Params(WindowSystem* windowSystem, OpenglSystem* openglSystem):
			windowSystem(windowSystem),
			openglSystem(openglSystem)
		{}
		
		WindowSystem* windowSystem;
		OpenglSystem* openglSystem;
		const char* glVersion = "#version 450";
	};
	
	ImGuiSystem(const Params& params);
	
	bool Init(bool bStatus) override;

	void Destroy() override;

	const Params& GetParmas() const { return _params; }

private:
	Params _params;
};
}