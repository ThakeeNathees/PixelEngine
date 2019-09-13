#include "pch.h"
#include "Scene.h"

#include "Application.h"

namespace pe
{
	int Signal::s_signal_count = 0;
	int Scene::s_scene_count = 0;
	int Scene::s_next_id = static_cast<int>(Asset::Type::Scene);

	Scene::Scene(std::string name) : m_name(name) {
		s_scene_count++;
		m_id = s_next_id++;
	}
	Scene::Scene() {
		s_scene_count++;
		m_id = s_next_id++;
		m_name = std::string("scn_").append(std::to_string(m_id));
	}

	Scene::~Scene() {
		s_scene_count--;
	}
	bool Scene::sortCompare(pe::Drawable* obj1, pe::Drawable* obj2) {
		return obj1->getZindex() < obj2->getZindex();
	}

	void Scene::clear()
	{
		m_timers.clear();
		m_signals.clear();
	}

	// setters
	void Scene::addObject(Object* object) {
		for (auto obj : m_objects) if (obj == object) return;
		m_objects.push_back(object);
		m_drawables.push_back(object);
		object->setScene(this);
		sortZIndex();
	}
	void Scene::sortZIndex() {
		std::sort(m_drawables.begin(), m_drawables.end(), Scene::sortCompare);
	}
	void Scene::setBackground(Background* background) {
		m_background = background;
		m_background->setTextureRectSize(Application::getWindowSize());
	}

	/*
	void Scene::setSceneWindowSize(sf::Vector2i window_size) {
		m_window_size = window_size;
		if (m_background != nullptr) m_background->setTextureRectSize(m_window_size);
	}
	*/

	void Scene::addTimer(Timer* timer) {
		m_timers.push_back(timer);
		timer->m_scene = this;
	}

	// getters
	Object* Scene::getObject(const std::string& name) {
		for ( Object* object : m_objects ) {
			if (object->getName() == name) return object;
		}
		return nullptr;
	}

}