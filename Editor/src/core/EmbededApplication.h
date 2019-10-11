#pragma once
#include "pch.h"
#include "core/CLI.h"

class EmbededApplication
{
public:	bool m_open = true; // for main menu bar

private:
	EmbededApplication() {}

	static EmbededApplication* s_instance;
	bool m_reload_on_save = true;
	pe::_peproj m_peproj;

	bool m_has_error = false;
	bool m_is_running = false;
	bool m_is_window_focus = false;
	bool m_is_application_reloaded = false;

	pe::Application* m_application;
	sf::RenderTexture m_render_texture;
	sf::RenderTexture m_default_texture;

	sf::Vector2f m_mouse_pos;


public:

	// getters
	static EmbededApplication* getInstance() {
		if (s_instance == nullptr) s_instance = new EmbededApplication();
		return s_instance;
	}
	
	pe::Application* getApplication() { return m_application; }
	bool isRunning() const { return m_is_running; }
	bool hasError() const { return m_has_error; }
	bool isOpen() const { return m_open; }
	bool isReloadOnSave() const { return m_reload_on_save; }

	sf::Vector2f getMousePosition() const {
		return m_mouse_pos;
	}
	bool isWindowFocus() const { return m_is_window_focus; }

	// setters
	void setError(bool has_error) { m_has_error = has_error; }
	void setReloadOnSave(bool reload_on_save) { m_reload_on_save = reload_on_save; }

	// methods
	void start() {
		reloadApplication();
		m_is_running = true;
		m_open = true;
	}
	void stop() { m_is_running = false; } // TODO: delete application if needed


	void reloadApplication();

	void reloadScripts();

	void render();

};