#include "engine.h"
#include <algorithm>
#include <unordered_set>
#include <fstream>
#include <iostream>
#include <string>

Engine::Engine()
{
    _grid = std::make_unique<std::unique_ptr<int[]>[]>(GRID_HEIGHT);
    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        _grid[i] = std::make_unique<int[]>(GRID_WIDTH);
        for (int j = 0; j < GRID_WIDTH; j++)
        {
            _grid[i][j] = Cell::State::DEAD;
        }
    }
}

void Engine::update()
{
    std::unordered_set<Cell> tmpAliveCells;
    std::unordered_set<Cell> tmpDeadCells;

    for (const auto &cell : _aliveCells)
    {
        int count = countAdjacentAliveCell(cell);
        if (count < 2 || count > 3)
        {
            tmpDeadCells.insert(cell);
        }
    }

    for (const auto &cell : _aliveCells)
    {
        auto adjacentDeadCells = getAdjacentDeadCells(cell);
        for (const auto &deadCell : adjacentDeadCells)
        {
            int aliveCount = countAdjacentAliveCell(deadCell);
            if (aliveCount == 3)
            {
                tmpAliveCells.insert(deadCell);
            }
        }
    }

    for (const auto &cell : tmpDeadCells)
    {
        _aliveCells.erase(std::remove(_aliveCells.begin(), _aliveCells.end(), cell), _aliveCells.end());
        _grid[cell.y][cell.x] = Cell::State::DEAD;
    }

    for (const auto &cell : tmpAliveCells)
    {
        if (std::find(_aliveCells.begin(), _aliveCells.end(), cell) == _aliveCells.end())
        {
            _aliveCells.emplace_back(cell);
            _grid[cell.y][cell.x] = Cell::State::ALIVE;
        }
    }
}

const std::unique_ptr<std::unique_ptr<int[]>[]> &Engine::getGrid()
{
    return _grid;
}

int Engine::countAdjacentAliveCell(const Cell &cell)
{
    int count = 0;

    const int neighborOffsets[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1}, // Top-left, Top, Top-right
        {0, -1},                    // Left
        {0, 1},                     // Right
        {1, -1},
        {1, 0},
        {1, 1} // Bottom-left, Bottom, Bottom-right
    };

    for (const auto &offset : neighborOffsets)
    {
        int neighborX = cell.x + offset[0];
        int neighborY = cell.y + offset[1];

        if (neighborX >= 0 && neighborX < GRID_WIDTH &&
            neighborY >= 0 && neighborY < GRID_HEIGHT)
        {
            if (_grid[neighborY][neighborX] == Cell::State::ALIVE)
            {
                count++;
            }
        }
    }

    return count;
}

std::vector<Cell> Engine::getAdjacentDeadCells(const Cell &cell)
{
    std::vector<Cell> deadCells;
    const int neighborOffsets[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    for (const auto &offset : neighborOffsets)
    {
        int neighborX = cell.x + offset[0];
        int neighborY = cell.y + offset[1];

        if (neighborX >= 0 && neighborX < GRID_WIDTH &&
            neighborY >= 0 && neighborY < GRID_HEIGHT &&
            _grid[neighborY][neighborX] == Cell::State::DEAD)
        {
            deadCells.emplace_back(neighborX, neighborY);
        }
    }

    return deadCells;
}

void Engine::setStartPattern(const std::string &pattern)
{
    std::ifstream file(pattern);
    if (!file.is_open())
    {
        std::cerr << "File " << pattern << " not found!\n";
        exit(1);
    }

    int i = 0;

    std::string line;
    while (std::getline(file, line) && i < GRID_HEIGHT)
    {
        for (int j = 0; j < line.length() && j < GRID_WIDTH; ++j)
        {
            if (line[j] != '.')
            {
                _grid[i][j] = Cell::State::ALIVE;
                _aliveCells.emplace_back(j, i);
            }
        }
        i++;
    }
}
