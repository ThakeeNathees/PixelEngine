#include "pch.h"

#include "Event.h"
#include "Font.h"
#include "Texture.h"

namespace pe
{
	int Texture::s_texture_count = 0;
	int Texture::s_next_id = static_cast<int>( Asset::Type::Texture );

	int Font::s_font_count = 0;
	int Font::s_next_id = static_cast<int>( Asset::Type::Font );
}