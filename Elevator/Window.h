#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <string>
using namespace std;

class Window
{
public:
	
	static const int WIDTH;
	static const int HEIGHT;
	static SDL_Window* window;
	static SDL_Renderer* renderer;

	class Text
	{
	public:

		static SDL_Texture* charset;
		static const int BMP_LETTER_SIZE;
		static const int LETTER_SIZE;

		static void drawString(int x, int y, const char* text)
		{
			int c;
			SDL_Rect src, dest;
			src.w = BMP_LETTER_SIZE;
			src.h = BMP_LETTER_SIZE;
			dest.w = LETTER_SIZE;
			dest.h = LETTER_SIZE;

			// text is pointer to the first letter in string
			while (*text != '\0')
			{
				// calculate letter position on bitmap
				c = *text & 255;
				src.x = (c % (2 * BMP_LETTER_SIZE)) * BMP_LETTER_SIZE;
				src.y = (c / (2 * BMP_LETTER_SIZE)) * BMP_LETTER_SIZE;

				// render letter
				dest.x = x;
				dest.y = y;
				SDL_RenderCopy(renderer, charset, &src, &dest);
				x += LETTER_SIZE;
				text++;
			}
		}

		static SDL_Point getCenteredTextPoint(SDL_Rect rect, const string& text)
		{
			int x = rect.x + rect.w / 2 - text.length() *LETTER_SIZE / 2;
			int y = rect.y + rect.h / 2 - LETTER_SIZE / 2;
			SDL_Point centered = {x,y};
			return centered;
		}

	};

	static void init(const string& title, SDL_Rect screenR, bool fullscreen)
	{
		int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN;

		window = SDL_CreateWindow(title.c_str(), screenR.x, screenR.y, screenR.w, screenR.h, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, 0);

		// setting text 
		SDL_Surface* charsetSurf = IMG_Load("assets/cs8x8.bmp");
		// odkomentować dla przeźroczystego tła literek
		SDL_SetColorKey(charsetSurf, true, 0x000000);
		// odkomentować dla zmiany koloru tekstu 
		//SDL_SetSurfaceColorMod(charsetSurf, 255, 0, 0);
		Text::charset = SDL_CreateTextureFromSurface(renderer, charsetSurf);
		SDL_FreeSurface(charsetSurf);

	}

	static void setDefaultBackgroundColor()
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}

	static SDL_Texture* loadIMG(std::string filename)
	{
		SDL_Surface* tmp = IMG_Load(filename.c_str());
		SDL_Texture* image = SDL_CreateTextureFromSurface(renderer, tmp);
		SDL_FreeSurface(tmp);
		return image;
	}

	static SDL_Rect createRect(int x, int y, int w, int h)
	{
		SDL_Rect tmp = { x, y, w, h };
		return tmp;
	}

	static void drawRect(SDL_Rect rect, int r, int g, int b)
	{
		SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		SDL_RenderFillRect(renderer, &rect);
		Window::setDefaultBackgroundColor();
	}

	static SDL_Rect generatePaddingRect(SDL_Rect rect, int horizontal, int vertical)
	{
		rect.x += horizontal;
		rect.y += vertical;
		rect.w -= horizontal * 2;
		rect.h -= vertical * 2;
		return rect;
	}

};

