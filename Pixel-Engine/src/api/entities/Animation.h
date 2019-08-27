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
			m_id = s_anim_count++;
			m_name = std::string("Animation_").append(std::to_string(m_id));
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
		inline void setName(const std::string& name) override { m_name = name; }

		// getters
		inline const Object& getObject() const {
			assert( hasObject() && "object is nullptr"  );
			return *m_object;
		}
		inline const std::string& getName() const override { return m_name; }
		inline int getId() const override { return m_id; }
		inline Type getType() const override { return Type::Animation; }

		inline bool getLoop() const { return m_loop; }
		inline bool getReverse() const { return m_reverse; }
		inline float getTimeLength() const { return m_time_length; }
		inline Signal& getAnimEndSignal() { return m_anim_end_signal; }

		inline const glm::fvec2& getBeginPosition() const { return m_begin_position; }
		inline const glm::fvec2& getBeginScale() const { return m_begin_scale; }
		inline const float getBeginRotation() const { return m_begin_rotation; }

		inline bool hasObject() const { return m_object != nullptr; }
		inline bool hasSpriteFrameTrack() const { return m_sprite_frame_track != nullptr; }
		inline bool hasPositionTrack() const { return m_position_track != nullptr; }
		inline bool hasRotationTrack() const { return m_rotation_track != nullptr; }
		inline bool hasScaleTrack() const { return m_scale_track != nullptr; }
		
		inline const SpriteFrameTrack& getSpriteFrameTrack() const { 
			assert( hasSpriteFrameTrack() && "sprite frame track is nullptr"); 
			return *m_sprite_frame_track; 
		}
		inline const PositionTrack& getPositionTrack() const {
			assert(hasPositionTrack() && "position track is nullptr");
			return *m_position_track;
		}
		inline const RotationTrack& getRotationTrack() const {
			assert( hasRotationTrack() && "rotation track is nullptr" );
			return *m_rotation_track;
		}
		inline const ScaleTrack& getScaleTrack() const {
			assert( hasRotationTrack() && "scale track is nullptr" );
			return *m_scale_track;
		}

	private:
		void emitSignal();

	private:  // TODO: add auto time length
		friend class Application;
		friend class AssetsReader; // set id

		std::string m_name;
		static int s_anim_count;
		int m_id;

		bool m_loop		 = true;
		bool m_reverse	 = false;
		Object* m_object = nullptr;
		int m_object_id = -1; // temp data needed when deserializing
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