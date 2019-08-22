#include "pch.h"
#include "../Scene.h"

namespace pe
{
	
	Timer::Timer()
		: m_signal(Signal("timeout"))
	{}

	Timer::Timer(const std::string& name, float time)
		: m_signal(Signal("timeout")), m_name(name), m_time(time)
	{}

	void Timer::start(float time) {
		m_time = time;
		m_clock.restart();
	}

	void Timer::setSignalReciever(Object* obj) {
		m_signal_reciever = obj;
	}

	double Timer::getRemainingTime() const {
		return m_time - m_clock.getElapsedTime().asSeconds();		
	}

	void Timer::update() {
		if (getRemainingTime() < 0 && !m_signal_emitted) {
			if (m_signal_reciever != nullptr) m_signal.addReciever(m_signal_reciever);
			if (m_scene != nullptr) m_scene->addSignal(&m_signal);

			if (m_loop) m_clock.restart();
			else m_signal_emitted = true;
		}
	}
}