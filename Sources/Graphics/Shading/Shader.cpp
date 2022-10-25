#include "Shader.h"

#include <vector>
#include <GL/glew.h>

#include "ShaderPart.h"

bool HasErrors(unsigned shaderId)
{
    GLint isCompiled = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

        // std::vector<GLchar> errorLog(maxLength);
        // glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);
        // for (auto i: errorLog)
            // std::cout<<i;
        // std::cout<<std::endl;

        return true;
    }
    return false;
}

Shader::Shader(std::shared_ptr<ShaderPart> vShader,
    std::shared_ptr<ShaderPart> fShader,
    std::shared_ptr<ShaderPart> gShader):
    _parts({std::move(vShader), std::move(fShader), std::move(gShader)})
{
}

Shader::~Shader()
{
    Destroy();
}

bool Shader::Compile(bool bCompileParts)
{
    _glHandler = glCreateProgram();

    std::vector parts{_parts.vShader, _parts.fShader};
    if (_parts.gShader)
        parts.push_back(_parts.gShader);
    
    std::vector<unsigned> attachedShaders;
    for (const std::shared_ptr<ShaderPart>& part : parts)
    {
        if (!part->IsInit() && (!bCompileParts || !part->Compile()))
            continue;
        
        attachedShaders.push_back(part->GetHandler());
        glAttachShader(_glHandler, part->GetHandler());
    }
    glLinkProgram(_glHandler);
    
    return attachedShaders.size() == parts.size();
}

void Shader::Bind() const
{
    glUseProgram(_glHandler);
}

void Shader::Release()
{
    glUseProgram(0);
}

void Shader::SetUniform(const std::string& name, const UniformValue& value, bool bUnbind)
{
    Bind();
    int loc = GetUniformLocation(name);
    if (loc < 0)
        return;
	
    std::visit([&](auto&& arg)
    {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, unsigned>)
            glUniform1ui(loc, arg);
        else if constexpr (std::is_same_v<T, int>)
            glUniform1i(loc, arg);
        else if constexpr (std::is_same_v<T, float>)
            glUniform1f(loc, arg);
        else if constexpr (std::is_same_v<T, glm::vec2>)
            glUniform2f(loc, arg.x, arg.y);
        else if constexpr (std::is_same_v<T, glm::vec3>)
            glUniform3f(loc, arg.x, arg.y, arg.z);
        else if constexpr (std::is_same_v<T, glm::vec4>)
            glUniform4f(loc, arg.x, arg.y, arg.z, arg.w);
        else if constexpr (std::is_same_v<T, glm::mat2>)
            glUniformMatrix2fv(loc, 1, GL_FALSE, &arg[0][0]);
        else if constexpr (std::is_same_v<T, glm::mat3>)
            glUniformMatrix3fv(loc, 1, GL_FALSE, &arg[0][0]);
        else if constexpr (std::is_same_v<T, glm::mat4>)
            glUniformMatrix4fv(loc, 1, GL_FALSE, &arg[0][0]);
    }, value);
	
    if (bUnbind)
        Release();
}

int Shader::GetUniformLocation(const std::string& name)
{
    const auto it = _uniformCache.find(name);
    if (it != _uniformCache.end())
        return it->second;

    const int loc = glGetUniformLocation(_glHandler, name.c_str());
    if (loc >= 0)
        _uniformCache[name] = loc;
	
    return loc;
}

void Shader::Destroy()
{
    if (_glHandler)
    {
        Release();
        std::vector parts{_parts.vShader, _parts.fShader};
        if (_parts.gShader)
            parts.push_back(_parts.gShader);

        for (const std::shared_ptr<ShaderPart>& p : parts)
        {
            glDetachShader(_glHandler, p->GetHandler());
        }
        
        glDeleteProgram(_glHandler);
        _glHandler = 0;
    }
}
