#include "pch.h"
#include "Scene.h"

namespace pe
{
	Scene::~Scene() {
		for (Object* object : m_objects) {
			delete object;
		}
	}
	// setters
	void Scene::addObject(Object* object) { m_objects.push_back(object); }

	// getters
	std::vector<Object*>& Scene::getObjects() { return m_objects; }

}