#include "Geometry.h"
#include "OpenGL/ErrorHandle.h"


Geometry::Geometry(const Buffer& vbo)
{
	if (!vbo.Data.Ptr)
		return;
    
	_vbo = vbo;
    
	GLCall(glGenVertexArrays(1, &_vaoHandler))
	Bind();

	unsigned vboId = _vbo.Create();
	GLCall(glBindVertexArray(0))
    
	if (vboId == 0)
		return;
    
	GLCall(glDeleteBuffers(1, &vboId))
}

Geometry::~Geometry()
{
	Release();
	GLCall(glDeleteVertexArrays(1, &_vaoHandler))
}

void Geometry::Bind() const
{
    GLCall(glBindVertexArray(_vaoHandler))
}

void Geometry::Release()
{
    GLCall(glBindVertexArray(0))
}

void Geometry::Render()
{
	Bind();
	GLCall(glDrawArrays(_vbo.DrawType, 0, _vbo.Data.Count))
}
