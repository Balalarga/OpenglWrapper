#pragma once
#include <map>
#include <vector>
#include <memory>
#include <cassert>
#include "ISystem.h"

namespace Oglw
{
class ImGuiSystem;
class OpenglSystem;
class WindowSystem;
class SdlSystem;

class SystemManager
{
public:
	static SystemManager& Instance();

	SdlSystem* sdlSystem{};
	WindowSystem* windowSystem{};
	OpenglSystem* openglSystem{};
	ImGuiSystem* imguiSystem{};
	
	static SystemManager& Init();
	static void Destroy();

	template<class T, class ...TArgs>
	static std::enable_if_t<std::derived_from<T, ISystem>, T&> CreateSystem(TArgs&& ...args)
	{
		auto system = new T(std::forward<TArgs>(args)...);
		assert(!GetSystem(system->GetName()));
		Instance()._names.emplace(system->GetName(), Instance()._systems.size());
		Instance()._systems.emplace_back(system);
		return *system;
	}

	template<class T>
	static std::enable_if_t<std::derived_from<T, ISystem>, T*> GetSystem(const std::string& name)
	{
		if (auto existingSystem = GetSystem(name))
			return dynamic_cast<T*>(existingSystem);
		
		return nullptr;
	}
	
	static ISystem* GetSystem(const std::string& name)
	{
		const auto existingSystem = Instance()._names.find(name);
		if (existingSystem != Instance()._names.end())
			return Instance()._systems[existingSystem->second].get();
		
		return nullptr;
	}

	static void InitDefaults();
	
private:
	std::vector<std::unique_ptr<ISystem>> _systems;
	std::map<std::string, size_t> _names;
};
}