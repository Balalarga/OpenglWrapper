#include "Scene.h"

#include <ranges>

#include "Camera.h"
#include "Core/SceneObject.h"

Scene::Scene(glm::ivec2 screenSize):
	_camera(45.f, screenSize.x/(float)screenSize.y, 0.01f, 10000.f)
{
	_camera.SetLocation({0, 0, -1});
}

void Scene::Render()
{
	_camera.RequestMatrixUpdate();

	for (auto& [material, objects] : _materialObjects)
	{
		material->Bind();
		for (std::shared_ptr<SceneObject>& object : objects)
		{
			material->SetUniform("uMVP", _camera.GetMatrix() * object->GetMatrix());
			object->Render();
		}
	}
}

void Scene::Update(float time)
{
	for (std::shared_ptr<SceneObject>& object : _objects)
		object->Update(time);
}

void Scene::AddObject(const std::shared_ptr<SceneObject>& object)
{
	_objects.push_back(object);
	auto it = _materialObjects.find(object->GetMaterial());
	if (it != _materialObjects.end())
		it->second.push_back(object);
	else
		_materialObjects[object->GetMaterial()] = {object};
}
