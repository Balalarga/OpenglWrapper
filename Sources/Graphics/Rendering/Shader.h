#pragma once
#include <memory>
#include <string>


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

    int GetUniformLocation(const std::string& name) const;
    
private:
    struct {
        std::shared_ptr<ShaderPart> vShader;
        std::shared_ptr<ShaderPart> fShader;
        std::shared_ptr<ShaderPart> gShader;
    } _parts;
    
    unsigned _glHandler = 0;
};
