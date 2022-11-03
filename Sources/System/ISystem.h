#pragma once
#include <string>


namespace Oglw
{
class ISystem
{
public:
	ISystem(std::string name);
	virtual ~ISystem() = default;

	virtual bool Init(bool bStatus);
	virtual void Destroy();

	const std::string& GetName() const { return _name; }
	bool WasInit() const { return _bWasInit; }

	
protected:
	friend class SystemManager;
	void SetWasInit(bool bWas);

	
private:
	std::string _name;
	bool _bWasInit = false;
};
}