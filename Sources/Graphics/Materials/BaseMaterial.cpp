#include "BaseMaterial.h"

#include "Utils/ShaderLoader.h"

namespace Oglw
{
static std::string defaultVertShader = R"(#version 330

layout(location = 0)in vec3 iVert;
layout(location = 1)in vec4 iVertColor;

uniform mat4 uModelMatrix = mat4(1);

out vec4 vertColor;

void main()
{
    gl_Position = uModelMatrix * vec4(iVert, 1.0);
    vertColor = iVertColor;
})";

static std::string defaultFragShader = R"(#version 330

in vec4 vertColor;
out vec4 fragColor;

void main()
{
    fragColor = vertColor;
})";

ShaderInfo BaseMaterial::sDefaultShaderInfo = {
	ShaderPartInfo{
		"BaseMaterial/default.vert",
		defaultVertShader,
		{
			{"vec3", "iVert", 0},
			{"vec4", "iVertColor", 1},
		},
		{
			{"vec4", "vertColor"},
		},
		{
			{"mat4", "uModelMatrix"},
		}
	},
	ShaderPartInfo{
		"BaseMaterial/default.frag",
		defaultFragShader,
		{
				{"vec3", "vertColor", 0},
			},
			{
				{"vec4", "fragColor"},
			},
			{
			}
	}
};

BaseMaterial::BaseMaterial(std::shared_ptr<Shader> shader):
	IMaterial(std::move(shader)),
	_modelMatrix(1.f)
{
}

BaseMaterial::BaseMaterial():
	IMaterial(ShaderLoader::TryGetShader("BaseMaterialShader", sDefaultShaderInfo)),
	_modelMatrix(1.f)
{
    GetShader()->Compile();
}

void BaseMaterial::Prepare()
{
	SetUniform("uModelMatrix", _modelMatrix);
}

Buffer BaseMaterial::CreateBufferWithLayout(const DataPtr& data)
{
	return { data, BufferLayout().Float(3).Float(4) };
}
}
