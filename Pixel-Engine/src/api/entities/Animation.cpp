
#include "pch.h"
#include "Object.h"


namespace pe
{
	Track::Data SpriteFrameTrack::getData( float time, bool reverse ) const {
		Track::Data _ret;
		if (m_keys.size() == 0) { _ret.sprite_frame = -1; return _ret; }

		for (int i = 0; i < m_keys.size(); i++) {
			if (time <= m_keys[i].time) {
				if (i == 0) { _ret.sprite_frame = -1; return _ret; }
				_ret.sprite_frame = m_keys[i - 1].data.sprite_frame;
				return _ret;
			}
		}
		_ret.sprite_frame = m_keys[ m_keys.size() - 1 ].data.sprite_frame;
		return _ret;
	}
	

	void Animation::play(bool resume) {
		if (!resume) {
			auto time = m_clock.getElapsedTime().asSeconds();
			if (m_time_length < time && !m_loop ) { stop(); }
			if (!m_playing) { m_clock.restart(); m_playing = true; }
			m_time_pointer = time - ( glm::floor(time/m_time_length)*m_time_length );
			if (m_object != nullptr) {
				if (m_object->hasSprite()) {
					int frame = m_sprite_frame_track->getData(m_time_pointer).sprite_frame;
					if (frame >= 0) m_object->getSprite().setFrameIndex( frame );
				}
			}
		}
		else {
			// TODO:
		}
	}

	void Animation::stop() {
		m_playing = false;
	}
}
