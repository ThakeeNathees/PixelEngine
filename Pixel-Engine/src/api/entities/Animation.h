#pragma once
#include "..//core.h"


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
		Data getData(float time, bool reverse = false) const override;
	};

	class PIXEL_ENGINE_API PositionTrack : public Track
	{
		//Data getData(float time, bool reverse = false) const override;
	};

	class PIXEL_ENGINE_API RotationTrack : public Track
	{
		//Data getData(float time, bool reverse = false) const override;
	};

	class PIXEL_ENGINE_API ScaleTrack : public Track
	{
		//Data getData(float time, bool reverse = false) const override;
	};

	/*	Class Animationl Begins	*/


	class Object;

	class PIXEL_ENGINE_API Animation
	{
	public:
		inline Animation(std::string name) : m_name(name)  {}

		// setters
		inline void setLoop(bool loop) { m_loop = loop; }
		inline void setRelative(bool relative) { m_relative = relative; }
		inline void getReverse(bool reverse) { m_reverse = reverse; }
		inline void setSpriteFrameTrack(SpriteFrameTrack* sprite_frame_track) { m_sprite_frame_track = sprite_frame_track; }
		inline void setObject(Object* object) { m_object = object; }

		// getters
		inline bool getLoop() const { return m_loop; }
		inline bool getRelative() const { return m_relative; }
		inline bool getReverse() const { return m_reverse; }
		inline std::string getName() const { return m_name; }
		

	private:
		std::string m_name;
		bool m_loop		= true;
		bool m_reverse	= false;
		bool m_relative = true; // relative position, rotation, scale or absolute ...

		// tracks
		SpriteFrameTrack* m_sprite_frame_track;
		Object* m_object = nullptr;
	};
}