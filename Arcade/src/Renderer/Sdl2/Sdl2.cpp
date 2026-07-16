/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Sdl2
*/

#include "Sdl2.hpp"

Arc::Sdl2::Sdl2() : _window(nullptr), _renderer(nullptr), _font(nullptr)
{
}

Arc::Sdl2::~Sdl2()
{
    if (_font)
        TTF_CloseFont(_font);
    for (auto& pair : _font_cache) {
        if (pair.second)
            TTF_CloseFont(pair.second);
    }
    _font_cache.clear();
    for (auto& pair : _texture_cache) {
        if (pair.second)
            SDL_DestroyTexture(pair.second);
    }
    _texture_cache.clear();
    if (_renderer)
        SDL_DestroyRenderer(_renderer);
    if (_window)
        SDL_DestroyWindow(_window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Arc::Sdl2::display(std::map<std::string, Item> &itemList)
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	SDL_RenderClear(_renderer);

	renderItems(itemList);

	SDL_RenderPresent(_renderer);
}

bool Arc::Sdl2::pollEvent(Event& event)
{
	SDL_Event e;

	if (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			event.type = Quit;
			return true;
		}
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
			event.type = Quit;
			return true;
		}
		if (e.type == SDL_KEYDOWN) {
			event.type = KeyPressed;
			switch (e.key.keysym.sym) {
				case SDLK_a:
					event.code = Arc::A;
					return true;
				case SDLK_b:
					event.code = Arc::B;
					return true;
				case SDLK_c:
					event.code = Arc::C;
					return true;
				case SDLK_d:
					event.code = Arc::D;
					return true;
				case SDLK_e:
					event.code = Arc::E;
					return true;
				case SDLK_f:
					event.code = Arc::F;
					return true;
				case SDLK_g:
					event.code = Arc::G;
					return true;
				case SDLK_h:
					event.code = Arc::H;
					return true;
				case SDLK_i:
					event.code = Arc::I;
					return true;
				case SDLK_j:
					event.code = Arc::J;
					return true;
				case SDLK_k:
					event.code = Arc::K;
					return true;
				case SDLK_l:
					event.code = Arc::L;
					return true;
				case SDLK_m:
					event.code = Arc::M;
					return true;
				case SDLK_n:
					event.code = Arc::N;
					return true;
				case SDLK_o:
					event.code = Arc::O;
					return true;
				case SDLK_p:
					event.code = Arc::P;
					return true;
				case SDLK_q:
					event.code = Arc::Q;
					return true;
				case SDLK_r:
					event.code = Arc::R;
					return true;
				case SDLK_s:
					event.code = Arc::S;
					return true;
				case SDLK_t:
					event.code = Arc::T;
					return true;
				case SDLK_u:
					event.code = Arc::U;
					return true;
				case SDLK_v:
					event.code = Arc::V;
					return true;
				case SDLK_w:
					event.code = Arc::W;
					return true;
				case SDLK_x:
					event.code = Arc::X;
					return true;
				case SDLK_y:
					event.code = Arc::Y;
					return true;
				case SDLK_z:
					event.code = Arc::Z;
					return true;
				case SDLK_0:
					event.code = Arc::Num0;
					return true;
				case SDLK_1:
					event.code = Arc::Num1;
					return true;
				case SDLK_2:
					event.code = Arc::Num2;
					return true;
				case SDLK_3:
					event.code = Arc::Num3;
					return true;
				case SDLK_4:
					event.code = Arc::Num4;
					return true;
				case SDLK_5:
					event.code = Arc::Num5;
					return true;
				case SDLK_6:
					event.code = Arc::Num6;
					return true;
				case SDLK_7:
					event.code = Arc::Num7;
					return true;
				case SDLK_8:
					event.code = Arc::Num8;
					return true;
				case SDLK_9:
					event.code = Arc::Num9;
					return true;
				case SDLK_LEFT:
					event.code = Arc::Left;
					return true;
				case SDLK_RIGHT:
					event.code = Arc::Right;
					return true;
				case SDLK_UP:
					event.code = Arc::Up;
					return true;
				case SDLK_DOWN:
					event.code = Arc::Down;
					return true;
				case SDLK_RETURN:
					event.code = Arc::Enter;
					return true;
				case SDLK_SPACE:
					event.code = Arc::Space;
					return true;
				case SDLK_TAB:
					event.code = Arc::Tab;
					return true;
				case SDLK_BACKSPACE:
					event.code = Arc::Backspace;
					return true;
				default:
					break;
			}
		}
		if (e.type == SDL_MOUSEBUTTONUP) {
			event.type = KeyPressed;
			if (e.button.button == SDL_BUTTON_LEFT) {
				event.code = MouseLeft;
			} else if (e.button.button == SDL_BUTTON_RIGHT) {
				event.code = MouseRight;
			}
			event.mouse = {e.button.x, e.button.y};
			return true;
		}
	}
	return false;
}

void Arc::Sdl2::createWindow(int width, int height, const std::string& title)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw ErrorCritical("Could not initialize Sdl2");

	_window = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_SHOWN	
	);
	if (!_window)
		throw ErrorCritical("Could not create Sdl2 window");

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (!_renderer)
		throw ErrorCritical("Could not create SDL2 renderer");

	if (TTF_Init() < 0)
		throw ErrorCritical("Could not initialize SDL2_ttf");

	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
		throw ErrorCritical("Could not initialize SDL2_image");

	_font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
	if (!_font)
		throw ErrorCritical("Could not load font ./arial.ttf");
}

TTF_Font* Arc::Sdl2::getFontForSize(int size)
{
	
	if (_font_cache.find(size) != _font_cache.end()) {
		return _font_cache[size];
	}

	TTF_Font* newFont = TTF_OpenFont(FONT_PATH, size);
	if (!newFont) {
		std::cerr << "Warning: Could not load font at size " << size << ", using default size" << std::endl;
		return _font;  
	}

	_font_cache[size] = newFont;
	return newFont;
}

SDL_Texture* Arc::Sdl2::getTextureForPath(const std::string& path)
{
	
	if (_texture_cache.find(path) != _texture_cache.end()) {
		return _texture_cache[path];
	}

	SDL_Surface* surface = IMG_Load(path.c_str());
	if (!surface) {
		std::cerr << "Warning: Could not load texture at path " << path << ": " << IMG_GetError() << std::endl;
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
	SDL_FreeSurface(surface);

	if (!texture) {
		std::cerr << "Warning: Could not create texture from surface for " << path << std::endl;
		return nullptr;
	}

	_texture_cache[path] = texture;
	return texture;
}

void Arc::Sdl2::renderItems(const std::map<std::string, Item>& items)
{
	
	std::vector<std::pair<std::string, Item>> sortedItems(items.begin(), items.end());
	std::sort(sortedItems.begin(), sortedItems.end(),
		[](const auto& a, const auto& b) {
			return a.second.drawOrder < b.second.drawOrder;
		});

	for (const auto& pair : sortedItems) {
		renderItem(pair.first, pair.second);
	}
}

void Arc::Sdl2::renderItem(const std::string& key, const Item& item)
{
	if (!item.texturePath.empty()) {
		renderTexture(item);
		return;
	}

	if (!item.text.empty()) {
		renderText(item);
	}
}

void Arc::Sdl2::clear()
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	SDL_RenderClear(_renderer);
}

void Arc::Sdl2::renderTexture(const Item& item)
{
    if (!_renderer)
        return;

    SDL_Texture* texture = getTextureForPath(item.texturePath);
    if (!texture)
        return;

    int texWidth, texHeight;
    SDL_QueryTexture(texture, nullptr, nullptr, &texWidth, &texHeight);

    int scaledWidth = static_cast<int>(texWidth * item.size.first);
    int scaledHeight = static_cast<int>(texHeight * item.size.second);

    SDL_Rect destRect;
    destRect.x = static_cast<int>(item.position.first - scaledWidth / 2.0f);
    destRect.y = static_cast<int>(item.position.second - scaledHeight / 2.0f);
    destRect.w = scaledWidth;
    destRect.h = scaledHeight;

    SDL_Point center;
    center.x = destRect.w / 2;
    center.y = destRect.h / 2;

    if (item.rotation != 0) {
        SDL_RenderCopyEx(_renderer, texture, nullptr, &destRect, static_cast<double>(item.rotation), &center, SDL_FLIP_NONE);
    } else {
        SDL_RenderCopy(_renderer, texture, nullptr, &destRect);
    }
}

void Arc::Sdl2::renderText(const Item& item)
{
	if (!_renderer)
		return;

	int fontSize = static_cast<int>(item.size.second);
	if (fontSize <= 0)
		fontSize = FONT_SIZE;

	TTF_Font* font = getFontForSize(fontSize);
	if (!font)
		return;

	SDL_Color textColor = {TEXT_COLOR_R, TEXT_COLOR_G, TEXT_COLOR_B, 255};

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, item.text.c_str(), textColor);
	if (!textSurface)
		return;

	int textWidth = textSurface->w;
	int textHeight = textSurface->h;

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(_renderer, textSurface);
	SDL_FreeSurface(textSurface);

	if (!textTexture)
		return;

	SDL_Rect destRect;
	destRect.x = static_cast<int>(item.position.first);
	destRect.y = static_cast<int>(item.position.second);
	destRect.w = textWidth;
	destRect.h = textHeight;

	SDL_RenderCopy(_renderer, textTexture, nullptr, &destRect);

	SDL_DestroyTexture(textTexture);
}

extern "C" {
	Arc::IRenderer* entryPoint([[maybe_unused]] std::map<std::string, Arc::Item>& itemList)
	{
		return new Arc::Sdl2();
	}

	int getLibraryType() {
		return static_cast<int>(Arc::LibraryType::Renderer); 
	}

	std::string getName() {
		return "Sdl2";
	}
}
