#pragma once
#include <vector>

#include "Camera.h"
#include "Core/Material.h"
#include "Core/SceneObject.h"


class Scene
{
public:
    Scene(glm::ivec2 screenSize);
    virtual ~Scene() = default;

    virtual void Render();
    virtual void Update(float time);

    template<class T, class ...TArgs>
    requires std::derived_from<T, SceneObject>
    std::shared_ptr<T> CreateObject(TArgs&& ...args)
    {
        std::shared_ptr<T> object = std::make_shared<T>(args...);
        AddObject(object);
        return object;
    }
    Camera& GetCamera() { return _camera; }


protected:
    void AddObject(const std::shared_ptr<SceneObject>& object);


private:
    Camera _camera;
    std::vector<std::shared_ptr<SceneObject>> _objects;
    std::map<std::shared_ptr<Material>, std::vector<std::shared_ptr<SceneObject>>> _materialObjects;
};
