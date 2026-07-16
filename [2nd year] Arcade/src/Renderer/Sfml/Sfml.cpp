/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Sfml
*/

#include "Sfml.hpp"

Arc::Sfml::Sfml() : _window(nullptr), _font(nullptr)
{
}

Arc::Sfml::~Sfml()
{
    if (_font)
        delete _font;
    for (auto& pair : _font_cache) {
        if (pair.second)
            delete pair.second;
    }
    _font_cache.clear();
    for (auto& pair : _texture_cache) {
        if (pair.second)
            delete pair.second;
    }
    _texture_cache.clear();
    if (_window)
        delete _window;
}

void Arc::Sfml::display(std::map<std::string, Item> &itemList)
{
    if (!_window)
        return;

    _window->clear(sf::Color::Black);
    renderItems(itemList);
    _window->display();
}

bool Arc::Sfml::pollEvent(Event& event)
{
    if (!_window)
        return false;

    sf::Event sf_event;
    if (!_window->pollEvent(sf_event))
        return false;

    if (sf_event.type == sf::Event::Closed) {
        event.type = Quit;
        return true;
    }
    if (sf_event.type == sf::Event::KeyPressed) {
        if (sf_event.key.code == sf::Keyboard::Escape) {
            event.type = Quit;
            return true;
        }
        event.type = KeyPressed;
        switch (sf_event.key.code) {
            case sf::Keyboard::A:
                event.code = Arc::A;
                return true;
            case sf::Keyboard::B:
                event.code = Arc::B;
                return true;
            case sf::Keyboard::C:
                event.code = Arc::C;
                return true;
            case sf::Keyboard::D:
                event.code = Arc::D;
                return true;
            case sf::Keyboard::E:
                event.code = Arc::E;
                return true;
            case sf::Keyboard::F:
                event.code = Arc::F;
                return true;
            case sf::Keyboard::G:
                event.code = Arc::G;
                return true;
            case sf::Keyboard::H:
                event.code = Arc::H;
                return true;
            case sf::Keyboard::I:
                event.code = Arc::I;
                return true;
            case sf::Keyboard::J:
                event.code = Arc::J;
                return true;
            case sf::Keyboard::K:
                event.code = Arc::K;
                return true;
            case sf::Keyboard::L:
                event.code = Arc::L;
                return true;
            case sf::Keyboard::M:
                event.code = Arc::M;
                return true;
            case sf::Keyboard::N:
                event.code = Arc::N;
                return true;
            case sf::Keyboard::O:
                event.code = Arc::O;
                return true;
            case sf::Keyboard::P:
                event.code = Arc::P;
                return true;
            case sf::Keyboard::Q:
                event.code = Arc::Q;
                return true;
            case sf::Keyboard::R:
                event.code = Arc::R;
                return true;
            case sf::Keyboard::S:
                event.code = Arc::S;
                return true;
            case sf::Keyboard::T:
                event.code = Arc::T;
                return true;
            case sf::Keyboard::U:
                event.code = Arc::U;
                return true;
            case sf::Keyboard::V:
                event.code = Arc::V;
                return true;
            case sf::Keyboard::W:
                event.code = Arc::W;
                return true;
            case sf::Keyboard::X:
                event.code = Arc::X;
                return true;
            case sf::Keyboard::Y:
                event.code = Arc::Y;
                return true;
            case sf::Keyboard::Z:
                event.code = Arc::Z;
                return true;
            case sf::Keyboard::Num0:
                event.code = Arc::Num0;
                return true;
            case sf::Keyboard::Num1:
                event.code = Arc::Num1;
                return true;
            case sf::Keyboard::Num2:
                event.code = Arc::Num2;
                return true;
            case sf::Keyboard::Num3:
                event.code = Arc::Num3;
                return true;
            case sf::Keyboard::Num4:
                event.code = Arc::Num4;
                return true;
            case sf::Keyboard::Num5:
                event.code = Arc::Num5;
                return true;
            case sf::Keyboard::Num6:
                event.code = Arc::Num6;
                return true;
            case sf::Keyboard::Num7:
                event.code = Arc::Num7;
                return true;
            case sf::Keyboard::Num8:
                event.code = Arc::Num8;
                return true;
            case sf::Keyboard::Num9:
                event.code = Arc::Num9;
                return true;
            case sf::Keyboard::Left:
                event.code = Arc::Left;
                return true;
            case sf::Keyboard::Right:
                event.code = Arc::Right;
                return true;
            case sf::Keyboard::Up:
                event.code = Arc::Up;
                return true;
            case sf::Keyboard::Down:
                event.code = Arc::Down;
                return true;
            case sf::Keyboard::Return:
                event.code = Arc::Enter;
                return true;
            case sf::Keyboard::Space:
                event.code = Arc::Space;
                return true;
            case sf::Keyboard::Tab:
                event.code = Arc::Tab;
                return true;
            case sf::Keyboard::BackSpace:
                event.code = Arc::Backspace;
                return true;
            default:
                break;
        }
    }
    if (sf_event.type == sf::Event::MouseButtonReleased) {
        if (sf_event.mouseButton.button == sf::Mouse::Left) {
            event.type = KeyPressed;
            event.code = MouseLeft;
            event.mouse.x = sf_event.mouseButton.x;
            event.mouse.y = sf_event.mouseButton.y;
            return true;
        } else if (sf_event.mouseButton.button == sf::Mouse::Right) {
            event.type = KeyPressed;
            event.code = MouseRight;
            event.mouse.x = sf_event.mouseButton.x;
            event.mouse.y = sf_event.mouseButton.y;
            return true;
        }
    }
    return false;
}

void Arc::Sfml::createWindow(int width, int height, const std::string& title)
{
    _window = new sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(width), static_cast<unsigned int>(height)), title);
    if (!_window)
        throw ErrorCritical("Could not create SFML window");

    _window->setFramerateLimit(60);

    _font = new sf::Font();
    if (!_font->loadFromFile(FONT_PATH))
        throw ErrorCritical("Could not load font " + std::string(FONT_PATH));
}

sf::Font* Arc::Sfml::getFontForSize(int size)
{
    if (_font_cache.find(size) != _font_cache.end()) {
        return _font_cache[size];
    }

    sf::Font* newFont = new sf::Font();
    if (!newFont->loadFromFile(FONT_PATH)) {
        std::cerr << "Warning: Could not load font at size " << size << ", using default size" << std::endl;
        delete newFont;
        return _font;
    }

    _font_cache[size] = newFont;
    return newFont;
}

sf::Texture* Arc::Sfml::getTextureForPath(const std::string& path)
{
    if (_texture_cache.find(path) != _texture_cache.end()) {
        return _texture_cache[path];
    }

    sf::Texture* texture = new sf::Texture();
    if (!texture->loadFromFile(path)) {
        std::cerr << "Warning: Could not load texture at path " << path << std::endl;
        delete texture;
        return nullptr;
    }

    _texture_cache[path] = texture;
    return texture;
}

void Arc::Sfml::renderItems(const std::map<std::string, Item>& items)
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

void Arc::Sfml::renderItem(const std::string& key, const Item& item)
{
    if (!item.texturePath.empty()) {
        renderTexture(item);
        return;
    }

    if (!item.text.empty()) {
        renderText(item);
    }
}

void Arc::Sfml::clear()
{
    if (!_window)
        return;

    _window->clear(sf::Color::Black);
}

void Arc::Sfml::renderTexture(const Item& item)
{
    if (!_window)
        return;

    sf::Texture* texture = getTextureForPath(item.texturePath);
    if (!texture)
        return;

    sf::Sprite sprite(*texture);
    sf::Vector2u texSize = texture->getSize();
    sprite.setScale(item.size.first, item.size.second);
    sprite.setOrigin(static_cast<float>(texSize.x) / 2.0f, static_cast<float>(texSize.y) / 2.0f);
    sprite.setRotation(static_cast<float>(item.rotation));
    sprite.setPosition(item.position.first, item.position.second);
    _window->draw(sprite);
}

void Arc::Sfml::renderText(const Item& item)
{
    if (!_window)
        return;

    int fontSize = static_cast<int>(item.size.second);
    if (fontSize <= 0)
        fontSize = FONT_SIZE;

    sf::Font* font = getFontForSize(fontSize);
    if (!font)
        return;

    sf::Text text(item.text, *font, static_cast<unsigned int>(fontSize));
    text.setPosition(sf::Vector2f(item.position.first, item.position.second));
    text.setFillColor(sf::Color(TEXT_COLOR_R, TEXT_COLOR_G, TEXT_COLOR_B));

    _window->draw(text);
}

extern "C" {
    Arc::IRenderer* entryPoint([[maybe_unused]] std::map<std::string, Arc::Item>& itemList)
    {
        return new Arc::Sfml();
    }
    
    int getLibraryType() {
        return static_cast<int>(Arc::LibraryType::Renderer); 
    }

    std::string getName() {
        return "Sfml";
    }
}
