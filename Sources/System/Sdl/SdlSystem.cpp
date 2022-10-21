#include "SdlSystem.h"

#include <SDL.h>
#include "Utils/Macroses.h"


SdlSystem::SdlSystem(const Params& inParams):
	ISystem(TOSTRING(SdlSystem)),
	_params(inParams),
	_displayInfo()
{
}

bool SdlSystem::Init(bool bStatus)
{
	if (SDL_Init(_params.Subsystems) != 0)
		return false;
	
	SDL_GetDesktopDisplayMode(0, &_displayInfo);
	
	return true;
}

void SdlSystem::Destroy()
{
	if (WasInit())
	{
		SDL_Quit();
	}
}
