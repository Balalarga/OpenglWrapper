#include "Object.h"

#include <GL/glew.h>

Object::Object(const Buffer& vbo, const Material& material, Texture2d* texture):
	_vbo(vbo),
	_material(material),
	_texture(texture)
{
	assert(_vbo.Data.Ptr);
    
	glGenVertexArrays(1, &_glHandler);
	glBindVertexArray(_glHandler);

	unsigned vboId = _vbo.Create();
	glBindVertexArray(0);
    
	glDeleteBuffers(1, &vboId);
}

Object::~Object()
{
	glDeleteVertexArrays(1, &_glHandler);
}

void Object::Render() const
{
	if (_texture)
		_texture->Bind();
	_material.Bind();
	glBindVertexArray(_glHandler);
	glDrawArrays(_vbo.DrawType, 0, _vbo.Data.Count);
}
