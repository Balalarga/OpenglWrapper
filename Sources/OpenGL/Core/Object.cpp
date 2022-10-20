#include "Object.h"
#include "Geometry.h"
#include "Shader.h"
#include "Texture2d.h"

Object::Object(Geometry* geometry, Shader* shader, Texture2d* texture):
	_geometry(geometry),
	_shader(shader),
	_texture(texture)
{
}

void Object::Render()
{
	if (_texture)
		_texture->Bind();
	
	_shader->Bind();
	_shader->SetUniform("uTexture", 0);
	_geometry->Bind();
	
	_geometry->Render();
}
