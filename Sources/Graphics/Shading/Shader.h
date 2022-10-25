#pragma once
#include <map>
#include <memory>
#include <string>

#include "Uniform.h"


class ShaderPart;

class Shader
{
public:
    Shader(std::shared_ptr<ShaderPart> vShader,
        std::shared_ptr<ShaderPart> fShader,
        std::shared_ptr<ShaderPart> gShader = nullptr);
    ~Shader();
    
    bool Compile(bool bCompileParts = false);
    void Destroy();
    
    void Bind() const;
    static void Release();

    void SetUniform(const std::string& name, const UniformValue& value, bool bUnbind = false);
    
protected:
    int GetUniformLocation(const std::string& name);
    
private:
    struct {
        std::shared_ptr<ShaderPart> vShader;
        std::shared_ptr<ShaderPart> fShader;
        std::shared_ptr<ShaderPart> gShader;
    } _parts;
    
    unsigned _glHandler = 0;
    
    std::map<std::string, int> _uniformCache;
};
