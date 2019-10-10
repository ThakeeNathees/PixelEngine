#pragma once
#include "..//core.h"


namespace pe
{
	class Object;


	class PIXEL_ENGINE_API Signal
	{
	public:
		enum class Type
		{
			CUSTOM,
			ANIMATION_END,
			SCENE_CHANGE,
			// TODO:  add more
		};

		struct _AnimEndSignal {
			int anim_id;
			const char* anim_name;
		};
		struct _SceneChange{
			int scene_id;
			const char* scene_name;
		};

		union {
			void* custom_data =nullptr;
			_AnimEndSignal anim_end_data;
			_SceneChange scene_change_data;
		};

	//////////////////////////////////////////////////////
		inline Signal(Type type = Type::CUSTOM) {
			m_id = s_signal_count++;
			m_type = type;
			m_name = std::string( "Signal_").append(std::to_string(m_id));
		}
		Signal(std::string name, Type type = Type::CUSTOM) : m_name(name) {
			m_type = type;
			m_id = s_signal_count++;
		}
		~Signal() {}
		// noone delets new signal now

		// setters
		inline void addReciever( Object* reciever) { m_recievers.push_back(reciever); }
		inline void setName(std::string name) { m_name; }
		inline void clear() { m_recievers.clear(); }

		// getters
		inline static int getCount() { return s_signal_count; }
		inline std::vector<Object*>& getRecievers() { return m_recievers; }
		inline Object& getSender() const {
			if (m_sender == nullptr) throw std::exception("Error: in pe::Signal::getSender() const\n\tsender was null");
			return *m_sender;
		}
		inline bool hasSender() const { return m_sender != nullptr; }
		inline const std::string& getName() const { return m_name; }
		Type getType() const { return m_type; }


	private:
		std::string m_name;
		static int s_signal_count; // = 0; in Scene.cpp
		int m_id;
		Type m_type = Type::CUSTOM;
		friend class Object; // for access m_sender;
		friend class Timer;
		Object* m_sender = nullptr;
		std::vector<Object*> m_recievers;
	};
}
