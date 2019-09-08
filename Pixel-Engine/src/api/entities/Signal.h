#pragma once
#include "..//core.h"


namespace pe
{
	class Object;


	class PIXEL_ENGINE_API Signal
	{
	public:
		inline Signal() {
			m_id = s_signal_count++;
			m_name = std::string( "Signal_").append(std::to_string(m_id));
		}
		inline Signal(std::string name) : m_name(name) {
			m_id = s_signal_count++;
		}
		// noone delets new signal now

		// setters
		inline void addReciever( Object* reciever) { m_recievers.push_back(reciever); }
		inline void setName(std::string name) { m_name; }
		inline void clear() { m_recievers.clear(); }

		template <typename T=void*>
		void setData(T data) { m_data = (void*)data; }

		// getters
		inline static int getCount() { return s_signal_count; }
		inline std::vector<Object*>& getRecievers() { return m_recievers; }
		inline Object& getSender() const { assert( m_sender != nullptr );  return *m_sender; }
		inline bool hasSender() const { return m_sender != nullptr; }
		inline const std::string& getName() const { return m_name; }

		template <typename T=void*>
		T getData() { return (T)m_data; }

	private:
		std::string m_name;
		static int s_signal_count; // = 0; in Scene.cpp
		int m_id;
		void* m_data;
		friend class Object; // for access m_sender;
		friend class Timer;
		Object* m_sender = nullptr;
		std::vector<Object*> m_recievers;
	};
}
