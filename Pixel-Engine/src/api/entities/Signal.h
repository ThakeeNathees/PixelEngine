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
		union Data;
		inline void addReciever( Object* reciever) { m_recievers.push_back(reciever); }
		inline void setName(std::string name) { m_name; }
		inline void clear() { m_recievers.clear(); }

		inline void setData(const Data& data) { m_data = data; }

		// getters
		inline std::vector<Object*>& getRecievers() { return m_recievers; }
		inline Object& getSender() const { assert( m_sender != nullptr );  return *m_sender; }
		inline const std::string& getName() const { return m_name; }

		inline Data getData() { return m_data; }

		union Data {
		public:
			Data() { double_data = 0; };
			Data(int data) { int_data = data; }
			Data(const char* data) { str_data = data; }
			Data(short data) { short_data = data; }
			Data(long data) { long_data = data; }
			Data(float data) { float_data = data; }
			Data(double data) { double_data = data; }
			Data(sf::Vector2f data) { vec_data = data; }
			
			const char* str_data;
			char char_data;
			int int_data;
			short short_data;
			long long_data;
			float float_data;
			double double_data;

			int id;
			const char* anim_name;
			sf::Vector2f vec_data;
		};

	private:
		std::string m_name;
		static int s_signal_count; // = 0; in Scene.cpp
		int m_id;
		Data m_data;
		friend class Object; // for access m_sender;
		friend class Timer;
		Object* m_sender = nullptr;
		std::vector<Object*> m_recievers;
	};
}
