#pragma once

enum class directions : size_t
{
    up = 0,
    down = 1,
    left = 2,
    right = 3
};

struct pos_t
{
    size_t row;
    size_t col;


    static pos_t getFrom(size_t pos)
    {
        pos_t p;
        p.row = pos / 4;
        p.col = pos - p.row * 4;

        return p;
    }

    size_t toSizeT()
    {
        return row * 4 + col;
    }
};