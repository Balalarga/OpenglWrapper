#pragma once
#include "Buffer.h"
#include <glm/glm.hpp>


class Geometry
{
public:
	Geometry(const Buffer& vbo);
    virtual ~Geometry();

	void Bind() const;
	static void Release();

	virtual void Render();
	
private:
	Buffer _vbo;
	GLuint _vaoHandler;

	glm::mat4 _modelMatrix{1.f};
};
