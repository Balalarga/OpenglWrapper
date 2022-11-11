#include "ISystem.h"

namespace Oglw
{
ISystem::ISystem(std::string name):
	_name(std::move(name))
{
	
}

bool ISystem::Init()
{
	return true;
}

void ISystem::Destroy()
{
	
}

void ISystem::SetWasInit(bool bWas)
{
	_bWasInit = bWas;
}
}