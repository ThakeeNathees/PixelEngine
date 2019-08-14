#include "pch.h"
#include "Scene.h"

namespace pe
{
	Scene::Scene(const char* name) : m_name(name) {}

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
		object->setScene(this);
		sortObjectsZIndex();
	}
	void Scene::sortObjectsZIndex() {
		std::sort(m_objects.begin(), m_objects.end(), Scene::sortCompare);
	}
	void Scene::setBackground(Background* background) {
		m_background = background;
		m_background->setVisible(true);
		m_background->setBgWindowSize(m_window_size);
	}

	void Scene::setSceneWindowSize(glm::ivec2 window_size) {
		m_window_size = window_size;
		if (m_background != nullptr) m_background->setBgWindowSize(m_window_size);
	}

	// getters

}