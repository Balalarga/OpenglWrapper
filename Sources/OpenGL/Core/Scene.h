#pragma once

#include <memory>
#include <vector>

#include "IRenderable.h"


class Object;

class Scene
{
public:
    Scene() = default;
    virtual ~Scene() = default;

    template<class T>
    T& AddObject(T*&& Obj)
    {
        _objects.push_back(std::unique_ptr<T>(Obj));
        return *_objects.back().get();
    }
    
    template<class T>
    T& AddRenderObject(T*&& Obj)
    {
        _renderObjects.push_back(std::unique_ptr<T>(Obj));
        return *_renderObjects.back().get();
    }
    
    const std::vector<std::unique_ptr<IRenderable>>& GetRenderObjects() const { return _renderObjects; }
    const std::vector<std::unique_ptr<Object>>& GetObjects() const { return _objects; }
    std::set<Shader*> GetShaders() const;


private:
    std::vector<std::unique_ptr<IRenderable>> _renderObjects;
    std::vector<std::unique_ptr<Object>> _objects;
};
