#include "Texture2dMaterial.h"

#include "Graphics/Texture/Texture2d.h"
#include "Utils/ShaderLoader.h"

namespace Oglw
{

std::string defaultVertShader = R"(#version 330

layout(location = 0)in vec3 iVert;
layout(location = 1)in vec4 iVertColor;
layout(location = 2)in vec2 iVertUv;

uniform mat4 uModelMatrix = mat4(1);
uniform vec3 uCameraPos;

out vec4 vertColor;
out vec2 vertUv;

void main()
{
    gl_Position = uModelMatrix * vec4(iVert, 1.0);
    vertColor = iVertColor;
    vertUv = iVertUv;
})";

std::string defaultFragShader = R"(#version 330

in vec2 vertUv;
in vec4 vertColor;
out vec4 fragColor;

uniform vec4 uColor;
uniform vec3 uCameraPos;
uniform sampler2D uTexture;

void main()
{
    fragColor = texture(uTexture, vertUv);
})";

Buffer Texture2dMaterial::CreateBufferWithLayout(const DataPtr& data)
{
	Buffer buffer = BaseMaterial::CreateBufferWithLayout(data);
	buffer.Layout.Float(2);
	return buffer;
}

Texture2dMaterial::Texture2dMaterial(std::shared_ptr<Shader> shader, Texture2d* texture):
	BaseMaterial(std::move(shader)),
	_texture(texture)
{
}

Texture2dMaterial::Texture2dMaterial(Texture2d* texture):
	BaseMaterial(ShaderLoader::LoadCode(defaultVertShader, defaultFragShader)),
	_texture(texture)
{
}

void Texture2dMaterial::Prepare()
{
	BaseMaterial::Prepare();
	_texture->Bind();
	SetUniform("uTexture", 0);
}
}