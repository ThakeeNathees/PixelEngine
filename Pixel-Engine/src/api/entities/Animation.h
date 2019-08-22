#pragma once
#include "..//core.h"

#include "Timer.h"

namespace pe
{
	class PIXEL_ENGINE_API Track
	{
	public:
		union Data {
			int sprite_frame;
			float rotation;
			glm::fvec2 position;
			glm::fvec2 scale;
		};
		struct Key {
			float time;
			Data data;
		};

		inline virtual void addKey(const Key& key) {
			m_keys.push_back(key);
			std::sort(m_keys.begin(), m_keys.end(), sortCompare);
		}
		virtual Data getData(float time, bool reverse = false) const = 0;
	private:
		friend class SpriteFrameTrack;
		friend class PositionTrack;
		friend class RotationTrack;
		friend class ScaleTrack;
		inline static bool sortCompare(const Key& key1, const Key& key2) {
			return key1.time < key2.time;
		}
		std::vector<Key> m_keys;
	};

	class PIXEL_ENGINE_API SpriteFrameTrack : public Track 
	{
	public:
		Data getData(float time, bool reverse = false) const override;
	};

	class PIXEL_ENGINE_API PositionTrack : public Track
	{
	public:
		//Data getData(float time, bool reverse = false) const override;
	};

	class PIXEL_ENGINE_API RotationTrack : public Track
	{
	public:
		//Data getData(float time, bool reverse = false) const override;
	};

	class PIXEL_ENGINE_API ScaleTrack : public Track
	{
	public:
		//Data getData(float time, bool reverse = false) const override;
	};

	/*	Class Animationl Begins	*/


	class Object;

	class PIXEL_ENGINE_API Animation
	{
	public:
		inline Animation(std::string name, float time_length = 1) : m_name(name)  {}

		void play(bool resume=false);
		void stop();

		// setters
		inline void setLoop(bool loop) { m_loop = loop; }
		inline void setRelative(bool relative) { m_relative = relative; }
		inline void getReverse(bool reverse) { m_reverse = reverse; }
		inline void setObject(Object* object) { m_object = object; } // will set by object
		inline void setTimeLength(float time_length) { m_time_length = time_length; }
		inline void setSpriteFrameTrack(SpriteFrameTrack* sprite_frame_track) { m_sprite_frame_track = sprite_frame_track; }

		// getters
		inline bool getLoop() const { return m_loop; }
		inline bool getRelative() const { return m_relative; }
		inline bool getReverse() const { return m_reverse; }
		inline std::string getName() const { return m_name; }
		inline float getTimeLength() const { return m_time_length; }
		

	private:  // TODO: add anim_end signal, add auto time length
		friend class Application;
		std::string m_name;
		bool m_loop		 = true;
		bool m_reverse	 = false;
		bool m_relative  = true; // relative position, rotation, scale or absolute ...
		Object* m_object = nullptr;

		bool m_playing = false;
		
		sf::Clock m_clock;
		float m_time_length;
		float m_time_pointer=0; // points where the anim is now => pause anim, resume

		// tracks
		SpriteFrameTrack* m_sprite_frame_track;
	};
}