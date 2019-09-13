#pragma once
#include "..//core.h"

#include "Asset.h"
#include "Timer.h"

namespace pe
{
	class PIXEL_ENGINE_API Track
	{
	public:
		union Data {
			Data() {}
			Data(int frame) : sprite_frame(frame) {}
			Data(float rot) : rotation(rot) {}
			Data(const sf::Vector2f& vec) : position(vec) {}
			int sprite_frame;
			float rotation;
			sf::Vector2f position;
			sf::Vector2f scale;
		};
		struct Key {
			Key() {}
			Key(float _time, const Data& _data) : time(_time), data(_data) {}
			float time;
			Data data;
		};

		inline virtual void addKey(const Key& key) {
			m_keys.push_back(key);
			std::sort(m_keys.begin(), m_keys.end(), sortCompare);
		}
		virtual std::pair<bool, Data> getData(float time) const = 0; // bool true? has valid data

		inline const std::vector<Key>& getKeys() const { return m_keys; }

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

	class PIXEL_ENGINE_API Animation : public Asset
	{
	public:

		inline Animation()
		{
			s_anim_count++;
			m_id = s_next_id++;
			m_name = std::string("anim_").append(std::to_string(m_id));
			m_anim_end_signal.anim_end_data.anim_id = m_id;
			m_anim_end_signal.anim_end_data.anim_name = m_name.c_str();
		}
		inline Animation(std::string name, float time_length = 1) 
			: m_name(name)
		{
			s_anim_count++;
			m_id = s_next_id++;
			m_anim_end_signal.anim_end_data.anim_id = m_id;
			m_anim_end_signal.anim_end_data.anim_name = m_name.c_str();
		}

		inline ~Animation() {
			if (m_sprite_frame_track) delete m_sprite_frame_track;
			if (m_position_track) delete m_position_track;
			if (m_rotation_track) delete m_rotation_track;
			if (m_scale_track) delete m_scale_track;
			s_anim_count--;
		}

		void play();
		inline void reset() { m_done_anim = false; m_time_pointer = 0; };
		void stop();

		// setters
		inline void setName(const std::string& name) override { m_name = name; }
		inline void setLoop(bool loop) { m_loop = loop; }
		inline void setReverse(bool reverse) { m_reverse = reverse; }
		inline void setObject(Object* object) { m_object = object; } // will set by object
		inline void setTimeLength(float time_length) { m_time_length = time_length; }
		
		inline void setSpriteFrameTrack(SpriteFrameTrack* sprite_frame_track) { m_sprite_frame_track = sprite_frame_track; }
		inline void setPositionTrack(PositionTrack* position_track) { m_position_track = position_track; }
		inline void setRotationTrack(RotationTrack* rotation_track) { m_rotation_track = rotation_track; }
		inline void setScaleTrack(ScaleTrack* scale_track) { m_scale_track = scale_track; }

		// getters
		inline const Object* getObject() const {return m_object;}
		inline const std::string& getName() const override { return m_name; }
		inline int getId() const override { return m_id; }
		inline Type getType() const override { return Type::Animation; }

		inline bool isLoop() const { return m_loop; }
		inline bool isReverse() const { return m_reverse; }
		inline float getTimeLength() const { return m_time_length; }
		inline Signal& getAnimEndSignal() { return m_anim_end_signal; }

		inline const sf::Vector2f& getBeginPosition() const { return m_begin_position; }
		inline const sf::Vector2f& getBeginScale() const { return m_begin_scale; }
		inline const float getBeginRotation() const { return m_begin_rotation; }
		
		inline const SpriteFrameTrack* getSpriteFrameTrack() const {  return m_sprite_frame_track;  }
		inline const PositionTrack* getPositionTrack() const { return m_position_track; }
		inline const RotationTrack* getRotationTrack() const { return m_rotation_track; }
		inline const ScaleTrack* getScaleTrack() const { return m_scale_track; }

	private:
		void emitSignal();

	private:  // TODO: add auto time length
		friend class Application;
		friend class FileHandler;

		std::string m_name;
		static int s_anim_count;
		static int s_next_id;
		int m_id;

		bool m_loop		 = true;
		bool m_reverse	 = false;
		Object* m_object = nullptr;
		int m_object_id = -1; // temp data needed when deserializing
		Signal m_anim_end_signal = Signal("anim_end", Signal::Type::ANIMATION_END);

		bool m_playing = false;
		bool m_done_anim = false;
		
		sf::Clock m_clock;
		float m_time_length =0;
		float m_time_pointer=0; // points where the anim is now

		sf::Vector2f m_begin_position = sf::Vector2f(0,0);
		sf::Vector2f m_begin_scale = sf::Vector2f(1,1);
		float m_begin_rotation = 0;

		// tracks
		SpriteFrameTrack* m_sprite_frame_track = nullptr;
		PositionTrack* m_position_track = nullptr;
		RotationTrack* m_rotation_track = nullptr;
		ScaleTrack* m_scale_track = nullptr;
	};
}