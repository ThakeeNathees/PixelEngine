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
		virtual std::pair<bool, Data> getData(float time) const = 0; // bool true? has valid data
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
		std::pair<bool, Data> getData(float time) const override;
	};

	class PIXEL_ENGINE_API PositionTrack : public Track
	{
	public:
		std::pair<bool, Data> getData(float time) const override;
	};

	class PIXEL_ENGINE_API RotationTrack : public Track
	{
	public:
		std::pair<bool, Data> getData(float time) const override;
	};

	class PIXEL_ENGINE_API ScaleTrack : public Track
	{
	public:
		std::pair<bool, Data> getData(float time) const override;
	};

	/*	Class Animationl Begins	*/


	class Object;

	class PIXEL_ENGINE_API Animation
	{
	public:

		inline Animation()
		{
			m_id = s_anim_count++;
			m_name = std::string("Animation_", m_id );		
		}
		inline Animation(std::string name, float time_length = 1) 
			: m_name(name)
		{
			m_id = s_anim_count++;
		}

		inline ~Animation() {
			if (m_sprite_frame_track) delete m_sprite_frame_track;
			if (m_position_track) delete m_position_track;
			if (m_rotation_track) delete m_rotation_track;
			if (m_scale_track) delete m_scale_track;
		}

		void play();
		inline void reset() { m_done_anim = false; m_time_pointer = 0; };
		void stop();

		// setters
		inline void setLoop(bool loop) { m_loop = loop; }
		inline void setReverse(bool reverse) { m_reverse = reverse; }
		inline void setObject(Object* object) { m_object = object; } // will set by object
		inline void setTimeLength(float time_length) { m_time_length = time_length; }
		inline void setSpriteFrameTrack(SpriteFrameTrack* sprite_frame_track) { m_sprite_frame_track = sprite_frame_track; }
		inline void setPositionTrack(PositionTrack* position_track) { m_position_track = position_track; }
		inline void setRotationTrack(RotationTrack* rotation_track) { m_rotation_track = rotation_track; }
		inline void setScaleTrack(ScaleTrack* scale_track) { m_scale_track = scale_track; }

		// getters
		inline bool getLoop() const { return m_loop; }
		inline bool getReverse() const { return m_reverse; }
		inline std::string getName() const { return m_name; }
		inline float getTimeLength() const { return m_time_length; }
		inline Signal& getAnimEndSignal() { return m_anim_end_signal; }
		
	private:
		void emitSignal();

	private:  // TODO: add auto time length
		friend class Application;

		std::string m_name;
		static int s_anim_count;
		int m_id;

		bool m_loop		 = true;
		bool m_reverse	 = false;
		Object* m_object = nullptr;
		Signal m_anim_end_signal = Signal("anim_end");

		bool m_playing = false;
		bool m_done_anim = false;
		
		sf::Clock m_clock;
		float m_time_length;
		float m_time_pointer=0; // points where the anim is now

		glm::fvec2 m_begin_position = glm::fvec2(0,0);
		glm::fvec2 m_begin_scale = glm::fvec2(1,1);
		float m_begin_rotation = 0;

		// tracks
		SpriteFrameTrack* m_sprite_frame_track = nullptr;
		PositionTrack* m_position_track = nullptr;
		RotationTrack* m_rotation_track = nullptr;
		ScaleTrack* m_scale_track = nullptr;
	};
}