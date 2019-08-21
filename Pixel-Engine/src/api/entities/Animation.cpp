
#include "pch.h"
#include "Object.h"


namespace pe
{
	Track::Data SpriteFrameTrack::getData( float time, bool reverse ) const {
		Track::Data _ret;

		for (int i = 0; i < m_keys.size(); i++) {
			if (time <= m_keys[i].time) {
				if (i == 0) { _ret.sprite_frame = -1; return _ret; }
				_ret.sprite_frame = m_keys[i - 1].data.sprite_frame;
				return _ret;
			}
		}
	}
	
}
