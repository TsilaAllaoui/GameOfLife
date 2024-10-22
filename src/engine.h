#ifndef __ENGINE_H__
#define __ENGINE_H__

#define GRID_WIDTH 64
#define GRID_HEIGHT 64

#include <memory>
#include <vector>
#include <list>
#include <string>

struct Cell
{
    int x;
    int y;
    Cell(const int &x_, const int &y_)
    {
        x = x_;
        y = y_;
    }
    enum State
    {
        ALIVE = 0xFFFFFFFF,
        DEAD = 0x0
    };
    bool operator==(const Cell &other) const
    {
        return x == other.x && y == other.y;
    }
};

namespace std
{
    template <>
    struct hash<Cell>
    {
        size_t operator()(const Cell &cell) const
        {
            return hash<int>()(cell.x) ^ hash<int>()(cell.y);
        }
    };
}

class Engine
{
    std::unique_ptr<std::unique_ptr<int[]>[]> _grid;
    std::vector<Cell> _aliveCells;

public:
    Engine();
    void update();
    const std::unique_ptr<std::unique_ptr<int[]>[]> &getGrid();
    int countAdjacentAliveCell(const Cell &);
    std::vector<Cell> getAdjacentDeadCells(const Cell &);
    void setStartPattern(const std::string &pattern);
};

#endif