#pragma once
#include <memory>

#include "AppWindow.h"
#include "Graphics/Rendering/IRender.h"
#include "System/ISystem.h"
#include "Utils/Macroses.h"

namespace Oglw
{
class WindowSystem: public ISystem
{
public:
	struct Params
	{
		AppWindow::Params windowParams{TOSTRING(AppWindow)};
	};

	WindowSystem(const Params& params);
	
	bool Init() override;
	void Destroy() override;

	AppWindow& GetWindow() { return *_window; }
	IRender* GetRender() const { return _render.get(); }

	template<class T, class ...TArgs>
	std::enable_if_t<std::derived_from<T, IRender>, T&> CreateRender(TArgs&& ...args)
	{
		T* render = new T(std::forward<TArgs>(args)...);
		_render.reset(render);
		return *render;
	}
	
private:
	Params _params;
	std::unique_ptr<AppWindow> _window;
	std::unique_ptr<IRender> _render;
};
}