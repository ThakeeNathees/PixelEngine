#include "pch.h"
#include "Scene.h"

namespace pe
{

	Scene::~Scene() {
		for (Object* object : m_objects) {
			delete object;
		}
	}
	bool Scene::sortCompare(Object* obj1, Object* obj2) {
		return obj1->getZIndex() < obj2->getZIndex();
	}

	// setters
	void Scene::addObject(Object* object) {
		m_objects.push_back(object);
		sortObjectsZIndex();
	}
	void Scene::sortObjectsZIndex() {
		std::sort(m_objects.begin(), m_objects.end(), Scene::sortCompare);
	}

	// getters

}