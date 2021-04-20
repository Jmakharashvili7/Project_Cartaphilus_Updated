#pragma once
#ifndef TEXT_H
#define TEXT_H

#include <SDL_ttf.h>

#include <string.h>
#include <iostream>
#include <vector>

#include "Commons.h"

class Texture2D;

// if we are in debug mode print LOG messages otherwise replace them with blank space
#ifdef PR_DEBUG
#define LOG(x) std::cout << x << std::endl
#else 
#define LOG(x) 
#endif

#define FONT_SLOT_CAPACITY 4

/* Text Manager class to handle rendering text to the screen. This is a singleton class meaning
   only one instance of the class may exist and the instane can be retrieved through Instance() 
   currently up to 4 fonts can be loaded in and saved. the fonts are accesed through a macro defined
   above. */

class TextManager
{
private:
	SDL_Texture* m_texture;
	SDL_Rect m_render_position;
	SDL_Renderer* m_renderer;
	TTF_Font* m_font;
public:
	TextManager(SDL_Renderer* renderer, const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& color);
	~TextManager();
	
	void RenderText(int x, int y);
private:
	SDL_Texture* LoadFont(SDL_Renderer* renderer, const std::string& message, const std::string& font_path, int font_size, SDL_Color color);
};
#endif // TEXT_H

