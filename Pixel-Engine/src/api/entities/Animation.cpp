
#include "pch.h"
#include "../Scene.h"


namespace pe
{
	std::pair<bool, Track::Data> SpriteFrameTrack::getData( float time ) const {
		std::pair<bool, Track::Data> _ret;
		_ret.first = true; _ret.second =  Track::Data();
		if (m_keys.size() == 0) { _ret.first = false; return _ret; }

		for (int i = 0; i < m_keys.size(); i++) {
			if (time <= m_keys[i].time) {
				if (i == 0) { _ret.first = false; return _ret; }
				_ret.second.sprite_frame = m_keys[i - 1].data.sprite_frame;
				return _ret;
			}
		}
		_ret.second.sprite_frame = m_keys[ m_keys.size() - 1 ].data.sprite_frame;
		return _ret;
	}
	
	std::pair<bool, Track::Data> PositionTrack::getData( float time) const {
		std::pair<bool, Track::Data> _ret;
		_ret.first = true; _ret.second = Track::Data();

		if (m_keys.size() == 0) { _ret.first = false; return _ret; }
		for (int i = 0; i < m_keys.size(); i++) {
			if (time < m_keys[i].time) {
				if (i == 0) { _ret.first = false; return _ret; }
				auto p1 = m_keys[i - 1].data.position;
				auto p2 = m_keys[i].data.position;
				auto t1 = m_keys[i - 1].time;
				auto t2 = m_keys[i].time;

				_ret.second.position = (time - t1) / (t2 - t1) * (p2 - p1) + p1;
				return _ret;
			}
		}
		_ret.second.position = m_keys[m_keys.size() - 1].data.position;
		return _ret;
	}

	std::pair<bool, Track::Data> RotationTrack::getData(float time) const {
		std::pair<bool, Track::Data> _ret;
		_ret.first = true; _ret.second = Track::Data();
		if (m_keys.size() == 0) { _ret.first = false; return _ret; }

		for (int i = 0; i < m_keys.size(); i++) {
			if (time <= m_keys[i].time) {
				if (i == 0) { _ret.first = false; return _ret; }
				auto p1 = m_keys[i - 1].data.rotation;
				auto p2 = m_keys[i].data.rotation;
				auto t1 = m_keys[i - 1].time;
				auto t2 = m_keys[i].time;
				_ret.second.rotation = (time - t1) / (t2 - t1) * (p2 - p1) + p1;
				return _ret;
			}
		}
		_ret.second.rotation = m_keys[m_keys.size() - 1].data.rotation;
		return _ret;
	}


	std::pair<bool, Track::Data> ScaleTrack::getData(float time) const {
		std::pair<bool, Track::Data> _ret;
		_ret.first = true; _ret.second = Track::Data();

		if (m_keys.size() == 0) { _ret.first = false; return _ret; }
		for (int i = 0; i < m_keys.size(); i++) {
			if (time < m_keys[i].time) {
				if (i == 0) { _ret.first = false; return _ret; }
				auto p1 = m_keys[i - 1].data.scale;
				auto p2 = m_keys[i].data.scale;
				auto t1 = m_keys[i - 1].time;
				auto t2 = m_keys[i].time;

				_ret.second.scale = (time - t1) / (t2 - t1) * (p2 - p1) + p1;
				return _ret;
			}
		}
		_ret.second.position = m_keys[m_keys.size() - 1].data.position;
		return _ret;
	}


	////////////////////////////////////////////////////////////////////////////////////
	void Animation::emitSignal() {
		if (m_object != nullptr) {
			m_object->emitSignal(m_anim_end_signal);
		}
	}

	void Animation::play() {
		if (m_done_anim) return;

		auto time = m_clock.getElapsedTime().asSeconds();
		if (!m_playing) {
			time = 0; m_clock.restart();
			m_playing = true;
			if (m_object) {
				m_begin_position	= pe::convertVect<glm::fvec2, sf::Vector2f>(m_object->getPosition());
				m_begin_scale		= pe::convertVect<glm::fvec2, sf::Vector2f>(m_object->getScale());
				m_begin_rotation	= m_object->getRotation();
			}
		}

		if (m_time_length < time ) { 
			time = 0; m_clock.restart();
			if (!m_loop) {
				emitSignal();
				stop();
				return;
			}
		}
		m_time_pointer = (!m_reverse)? time : m_time_length - time ;
		if (m_object != nullptr) {

			if (m_sprite_frame_track != nullptr) {
				if (m_object->hasSprite()) {
					auto data = m_sprite_frame_track->getData(m_time_pointer);
					if (data.first) m_object->getSprite().setFrameIndex(data.second.sprite_frame);
				}
			}
			if (m_rotation_track != nullptr) {
				auto data = m_rotation_track->getData(m_time_pointer);
				if (data.first) {
					m_object->setRotation( data.second.rotation + m_begin_rotation );
				}
			}
			if (m_position_track != nullptr) {
				auto data = m_position_track->getData( m_time_pointer );
				if (data.first) {
					m_object->setPosition(data.second.position + m_begin_position );
				}
			}
			if (m_scale_track != nullptr) {
				auto data = m_scale_track->getData(m_time_pointer);
				if (data.first) {
					glm::fvec2 new_scale;
					new_scale.x = data.second.scale.x * m_begin_scale.x;
					new_scale.y = data.second.scale.y * m_begin_scale.y;
					m_object->setScale( new_scale );
				}
			}
		}
	}

	void Animation::stop() {
		m_playing = false;
		m_done_anim = true;
	}
}
