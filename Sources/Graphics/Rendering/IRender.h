#pragma once

namespace Oglw
{
class IRender
{
public:
	virtual ~IRender() = default;
	
	virtual void Clear() = 0;
	virtual void Render() = 0;
	virtual void Present() = 0;
};
}