#pragma once

#include "Pixel-Engine/Core.h"
#include "Pixel-Engine/Window.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace PE
{
	class WindowsWindow : public Window
	{
	public:
		virtual ~WindowsWindow();
		void onUpdate() override;

		inline unsigned int getWidth() const override { return m_data.width; }
		inline unsigned int getHeight() const override { return m_data.height; }

		inline void setEventCallback(const EventCallbackFunc& callback) override { m_data.event_callback = callback; }
		void setVSync(bool enable) override;
		bool isVSync() const override;
	private:
		virtual void Init(const WindowProps& props);
		virtual void shutDown();

	private:
		sf::RenderWindow* m_window;
		
		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool VSync;
			EventCallbackFunc event_callback;
		};
		WindowData m_data;

	};
}