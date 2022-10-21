#include "ISystem.h"

ISystem::ISystem(std::string name):
	_name(std::move(name))
{
	
}

bool ISystem::Init(bool bStatus)
{
	return bStatus;
}

void ISystem::Destroy()
{
	
}

void ISystem::SetWasInit(bool bWas)
{
	_bWasInit = bWas;
}
