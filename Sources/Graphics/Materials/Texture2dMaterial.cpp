#include "Texture2dMaterial.h"

#include "Graphics/Texture/Texture2d.h"
#include "Utils/ShaderLoader.h"

namespace Oglw
{

static std::string defaultVertShader = R"(#version 330

layout(location = 0)in vec3 iVert;
layout(location = 1)in vec4 iVertColor;
layout(location = 2)in vec2 iVertUv;

uniform mat4 uModelMatrix = mat4(1);

out vec4 vertColor;
out vec2 vertUv;

void main()
{
    gl_Position = uModelMatrix * vec4(iVert, 1.0);
    vertColor = iVertColor;
    vertUv = iVertUv;
})";

static std::string defaultFragShader = R"(#version 330

in vec2 vertUv;
in vec4 vertColor;
out vec4 fragColor;

uniform sampler2D uTexture;

void main()
{
    fragColor = texture(uTexture, vertUv);
})";


ShaderInfo Texture2dMaterial::sDefaultShaderInfo = {
	ShaderPartInfo{
		"Texture2dMaterial/default.vert",
		defaultVertShader,
		{
				{"vec3", "iVert", 0},
				{"vec4", "iVertColor", 1},
				{"vec2", "iVertUv", 2},
			},
			{
				{"vec4", "vertColor"},
				{"vec2", "vertUv"},
			},
			{
				{"mat4", "uModelMatrix"},
			}
	},
	ShaderPartInfo{
		"Texture2dMaterial/default.frag",
		defaultFragShader,
		{
					{"vec3", "vertColor", 0},
					{"vec2", "vertUv", 0},
				},
				{
					{"vec4", "fragColor"},
				},
				{
					{"sampler2D", "uTexture"},
				}
	}
};

Buffer Texture2dMaterial::CreateBufferWithLayout(const DataPtr& data)
{
	return { data, BufferLayout().Float(3).Float(4).Float(2) };
}

Texture2dMaterial::Texture2dMaterial(std::shared_ptr<Shader> shader, Texture2d* texture):
	BaseMaterial(std::move(shader)),
	_texture(texture)
{
}

Texture2dMaterial::Texture2dMaterial(Texture2d* texture):
	BaseMaterial(ShaderLoader::TryGetShader("Texture2dMaterialShader", sDefaultShaderInfo)),
	_texture(texture)
{
    GetShader()->Compile();
}

void Texture2dMaterial::Prepare()
{
	BaseMaterial::Prepare();
	_texture->Bind();
	SetUniform("uTexture", 0);
}
}