/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Minesweeper
*/

#include "Minesweeper.hpp"

Arc::Minesweeper::Minesweeper(std::map<std::string, Item>& itemList) 
    : _grid(MINESWEEPER_WIDTH * MINESWEEPER_HEIGHT), _nb_flags(0), _game_state(INPROGRESS), _game_over(false), _has_started(false), _items(itemList)
{
    updateGrid();
}

Arc::Minesweeper::~Minesweeper()
{
}

void Arc::Minesweeper::update([[maybe_unused]] Event event)
{
    if (_game_state != INPROGRESS) {
        _items["game_over"] = {
            {620, 80},
            {30, 30},
            0,
            {1.0f, 1.0f},
            false,
            1,
            "",
            "Game Over !\nMenu: Space\nRestart: R",
            std::function<void()>()
        };
    }

    updateGrid();
}

void Arc::Minesweeper::handleKey(Event event)
{
    if (event.type == KeyPressed) {
        if (event.code == R) {
            _grid.assign(_grid.size(), Cell());
            _nb_flags = 0;
            _game_state = INPROGRESS;
            _game_over = false;
            _has_started = false;
            updateGrid();
            return;
        }
        if (event.code == MouseLeft) {
            std::size_t index = getCellIndexFromMouse(event.mouse.x, event.mouse.y);
            if (index < _grid.size()) {
                clickLeft(index);
            }
        } else if (event.code == MouseRight) {
            std::size_t index = getCellIndexFromMouse(event.mouse.x, event.mouse.y);
            if (index < _grid.size()) {
                clickRight(index);
            }
        }
        if (_game_state != INPROGRESS) {
            if (event.code == Space)
            _game_over = true;
        }
    }
}

std::size_t Arc::Minesweeper::getCellIndexFromMouse(int x, int y)
{
    const float CELL_SIZE_GAME = 50.0f;
    const float GRID_WIDTH = MINESWEEPER_WIDTH * CELL_SIZE_GAME;
    const float GRID_HEIGHT = MINESWEEPER_HEIGHT * CELL_SIZE_GAME;
    const float START_X = (1920.0f - GRID_WIDTH) / 2.0f;
    const float START_Y = (1080.0f - GRID_HEIGHT) / 2.0f;

    int cellX = (x - START_X) / CELL_SIZE_GAME;
    int cellY = (y - START_Y) / CELL_SIZE_GAME;

    if (cellX < 0 || cellX >= MINESWEEPER_WIDTH || cellY < 0 || cellY >= MINESWEEPER_HEIGHT) {
        return _grid.size();
    }

    std::size_t index = cellY * MINESWEEPER_WIDTH + cellX;
    return index;
}

void Arc::Minesweeper::updateGrid()
{

    const float CELL_SIZE_GAME = 50.0f;
    
    const float GRID_WIDTH = MINESWEEPER_WIDTH * CELL_SIZE_GAME;
    const float GRID_HEIGHT = MINESWEEPER_HEIGHT * CELL_SIZE_GAME;
    
    const float START_X = (1920.0f - GRID_WIDTH) / 2.0f;
    const float START_Y = (1080.0f - GRID_HEIGHT) / 2.0f;

    for (std::size_t i = 0; i < _grid.size(); ++i) {
        int col = i % MINESWEEPER_WIDTH;
        int row = i / MINESWEEPER_WIDTH;

        float x = START_X + col * CELL_SIZE_GAME;
        float y = START_Y + row * CELL_SIZE_GAME;
    
        std::string text = ".";
        if (_grid[i].is_flagged && !_grid[i].is_revealed)
            text = "F";
        else if (_grid[i].is_bomb && _grid[i].is_revealed)
            text = "B";
        else if (_grid[i].is_revealed && _grid[i].adjacent_bombs == 0)
            text = " ";
        else if (_grid[i].is_revealed)
            text = std::to_string(_grid[i].adjacent_bombs);
        else
            text = ".";

        _items["cell_" + std::to_string(i)] = {
            {x, y},
            {CELL_SIZE_GAME, CELL_SIZE_GAME},
            0,
            {1.0f, 1.0f},
            false,
            1,
            "",
            text,
            std::function<void()>()
        };
    }
}

void Arc::Minesweeper::handleCell()
{
}

bool Arc::Minesweeper::isAdjacent(std::size_t c1, std::size_t c2)
{
    if (c1 == c2)
        return false;

    const int x1 = c1 % MINESWEEPER_WIDTH;
    const int y1 = c1 / MINESWEEPER_WIDTH;

    const int x2 = c2 % MINESWEEPER_WIDTH;
    const int y2 = c2 / MINESWEEPER_WIDTH;

    return std::abs(x1 - x2) <= 1 && std::abs(y1 - y2) <= 1;
}

void Arc::Minesweeper::revealEmptyArea(std::size_t startIndex)
{
    if (startIndex >= _grid.size() || _grid[startIndex].is_revealed || _grid[startIndex].is_bomb || _grid[startIndex].is_flagged)
        return;
    
    std::queue<std::size_t> toReveal;
    toReveal.push(startIndex);
    
    while (!toReveal.empty()) {
        std::size_t index = toReveal.front();
        toReveal.pop();
        
        if (index >= _grid.size() || _grid[index].is_revealed || _grid[index].is_bomb || _grid[index].is_flagged)
            continue;
        
        _grid[index].is_revealed = true;
        
        if (_grid[index].adjacent_bombs > 0)
            continue;
        
        int x = index % MINESWEEPER_WIDTH;
        int y = index / MINESWEEPER_WIDTH;
        
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0)
                    continue;
                
                int nx = x + j;
                int ny = y + i;
                
                if (nx < 0 || ny < 0 || nx >= MINESWEEPER_WIDTH || ny >= MINESWEEPER_HEIGHT)
                    continue;
                
                std::size_t neighborIndex = static_cast<std::size_t>(ny * MINESWEEPER_WIDTH + nx);
                if (!_grid[neighborIndex].is_revealed && !_grid[neighborIndex].is_bomb && !_grid[neighborIndex].is_flagged) {
                    toReveal.push(neighborIndex);
                }
            }
        }
    }
}

void Arc::Minesweeper::spawnMines(std::size_t first_click)
{
    std::uint8_t nb_bombs = 0;
    std::size_t index = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, _grid.size() - 1);

    if (first_click >= _grid.size())
        return;

    for (std::size_t i = 0; i < _grid.size(); ++i) {
        _grid[i].is_bomb = false;
        _grid[i].is_revealed = false;
        _grid[i].is_flagged = false;
        _grid[i].adjacent_bombs = 0;
    }

    _nb_flags = 0;

    while (nb_bombs < MINESWEEPER_BOMBS) {
        index = dist(gen);
        if (!_grid[index].is_bomb && !isAdjacent(first_click, index)) {
            _grid[index].is_bomb = true;
            nb_bombs++;
        }
    }

    _has_started = true;
}

void Arc::Minesweeper::detectAdjacentMines()
{
    for (std::size_t index = 0; index < _grid.size(); ++index) {
        int x = index % MINESWEEPER_WIDTH;
        int y = index / MINESWEEPER_WIDTH;

        _grid[index].adjacent_bombs = 0;

        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {

                if (i == 0 && j == 0)
                    continue;

                int cx = x + j;
                int cy = y + i;

                if (cx < 0 || cy < 0 || cx >= MINESWEEPER_WIDTH || cy >= MINESWEEPER_HEIGHT)
                    continue;

                if (_grid[cy * MINESWEEPER_WIDTH + cx].is_bomb)
                    _grid[index].adjacent_bombs++;
            }
        }
    }
}

void Arc::Minesweeper::clickRight(std::size_t index)
{
    if (index >= _grid.size() || _game_state != INPROGRESS)
        return;
    if (_grid[index].is_revealed)
        return;
    if (_nb_flags >= MINESWEEPER_BOMBS && !_grid[index].is_flagged)
        return;
    (!_grid[index].is_flagged) ? _nb_flags++ : _nb_flags--;
    _grid[index].is_flagged = !_grid[index].is_flagged;

    for (std::size_t i = 0; i < _grid.size(); ++i)
        if (_grid[i].is_bomb && !_grid[i].is_flagged)
            return;
    _game_state = VICTORY;
}

void Arc::Minesweeper::clickLeft(std::size_t index)
{
    if (index >= _grid.size() || _game_state != INPROGRESS)
        return;
    
    if (!_has_started) {
        spawnMines(index);
        detectAdjacentMines();
    }
    
    if (_grid[index].is_revealed)
        return;
    
    if (_grid[index].is_flagged)
        return;
    
    if (_grid[index].is_bomb) {
        _grid[index].is_revealed = true;
        _game_state = DEFEAT;
        return;
    }
    
    if (_grid[index].adjacent_bombs == 0) {
        revealEmptyArea(index);
    } else {
        _grid[index].is_revealed = true;
    }

    for (std::size_t i = 0; i < _grid.size(); ++i) {
        if (!_grid[i].is_revealed && !_grid[i].is_bomb)
            return;
    }
    
    _game_state = VICTORY;
}

extern "C" {
	Arc::IGame* entryPoint([[maybe_unused]] std::map<std::string, Arc::Item>& itemList)
	{
		return new Arc::Minesweeper(itemList);
	}
	
	int getLibraryType() {
		return static_cast<int>(Arc::LibraryType::Game); 
	}

	std::string getName() {
		return "Minesweeper";
	}
}

void Arc::Minesweeper::display() const
{
    std::cout << "Minesweeper displayed\n";
}