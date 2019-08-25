#include "pch.h"
#include "../Scene.h"

namespace pe
{
	int Timer::s_timer_count = 0;

	Timer::Timer()
	{
		m_id = s_timer_count++;
		m_name = std::string("Timer_").append(std::to_string(m_id));
	}

	Timer::Timer(const std::string& name, float time, bool loop)
		:m_name(name), m_time(time), m_loop(loop)
	{
		m_id = s_timer_count++;
	}

	void Timer::start(float time) {
		m_running = true;
		if (time != -1) m_time = time;
		m_clock.restart();
	}

	double Timer::getRemainingTime() const {
		return m_time - m_clock.getElapsedTime().asSeconds();		
	}

	void Timer::stop() {
		m_running = false;
	}

	void Timer::update() {
		if (m_running) {
			if (getRemainingTime() < 0 && !m_signal_emitted) {
				if (m_scene != nullptr) m_scene->addSignal(&m_signal);

				if (m_loop) m_clock.restart();
				else {
					m_signal_emitted = true;
					m_running = false;
				}
			}
		}
	}
}