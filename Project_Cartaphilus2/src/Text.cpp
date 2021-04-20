#include "Text.h"

#include "Texture2D.h"

TextManager::TextManager(SDL_Renderer* renderer, const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& color) : m_renderer(renderer)
{
	m_texture = LoadFont(renderer, message_text, font_path, font_size, color);
	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_render_position.w, &m_render_position.h);
}

SDL_Texture* TextManager::LoadFont(SDL_Renderer* renderer, const std::string& message, const std::string& font_path, int font_size, SDL_Color color)
{
	// load the font and check if the font was loaded correctly
	m_font = TTF_OpenFont(font_path.c_str(), font_size);
	if (!m_font)
	{
		LOG("Font could not be loaded! " + std::string(TTF_GetError()));
	}

	// load the surface and check if it was loaded correctly
	SDL_Surface* surface = TTF_RenderText_Solid(m_font, message.c_str(), color);
	if (surface == NULL)
	{
		LOG("surface could not be loaded! " + std::string(SDL_GetError()));
	}
	
	// create a texture from the surface
	auto text_texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
	return text_texture;
}

// render the text
void TextManager::RenderText(int x, int y) 
{
	m_render_position.x = x;
	m_render_position.y = y;
	SDL_RenderCopy(m_renderer, m_texture, nullptr, &m_render_position);
}