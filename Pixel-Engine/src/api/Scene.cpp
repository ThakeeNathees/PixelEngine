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
		sortObjectsZIndex();
	}
	void Scene::sortObjectsZIndex() {
		std::sort(m_objects.begin(), m_objects.end(), Scene::sortCompare);
	}
	void Scene::loadBackgroundTexture( std::string path ) {
		m_bg_texture.loadFromFile(path);
		m_bg_texture.setRepeated(true);
		m_background.setTextureRect(sf::IntRect(0, 0, 700,700));
		m_background.setTexture(m_bg_texture );

		setBgVisible(true);
	}

	// getters

}