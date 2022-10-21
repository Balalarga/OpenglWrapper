#pragma once
#include <SDL.h>
#include "System/ISystem.h"

class SdlSystem: public ISystem
{
public:
	struct Params
	{
		Uint32 Subsystems = SDL_INIT_EVERYTHING;
	};
	
	SdlSystem(const Params& inParams);
	
	bool Init(bool bStatus) override;
	
	void Destroy() override;

	const SDL_DisplayMode& GetDisplayInfo() const { return _displayInfo; }
	const Params& GetParams() const { return _params; }
	
private:
	Params _params;
	SDL_DisplayMode _displayInfo;
};
