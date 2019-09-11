#pragma once
#include "../core.h"

#include "Signal.h"

namespace pe
{
	class Object;
	class Scene;

	class PIXEL_ENGINE_API Timer
	{
	public:
		Timer();
		Timer(const std::string& name, float time=0.f, bool loop = false);
		// delete by Object

		inline void setName(const std::string& name) { m_name = name; }
		inline void setScene(Scene* scene) { m_scene = scene; }
		void start(float time = -1);
		void stop();
		void update();

		inline void setLoop(bool loop) { m_loop = loop; }
		inline void setTime(float time) { m_time = time; }

		double getRemainingTime() const;
		inline const std::string& getName() const { return m_name; }
		inline float getTime() const { return m_time; }
		inline Signal& getTimeoutSignal() { return m_signal; }

	private:

		friend class Scene;
		friend class Object;
		std::string m_name;
		static int s_timer_count;
		int m_id;
		float m_time = 1.f; // default 1s
		bool m_loop = false;
		sf::Clock m_clock;
		Signal m_signal = Signal("timeout");
		Scene* m_scene = nullptr;

		bool m_running = false;
		bool m_signal_emitted = false;
	};
}