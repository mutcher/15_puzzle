#pragma once
#include <array>
#include <random>
#include <sstream>
#include <iomanip>

#include "directions.h"

class game_field
{
private:
    typedef unsigned char ubyte_t;
    std::array<ubyte_t, 16> _gameField;
    size_t _zeroPos;
    bool _fieldChanged;

private:
    inline void drawLine(std::stringstream& ss, ubyte_t firstChar, ubyte_t midChar, ubyte_t lastChar)
    {
        ss << firstChar;
        for(ubyte_t i = 0; i < 4; ++i)
        {
            if (i != 3)
            {
                ss << std::setfill<char>(205u) << std::setw(4) << midChar;
            }
            else
            {
                ss << std::setfill<char>(205u) << std::setw(4) << static_cast<char>(lastChar) << std::endl;
            }
        }
    }

public:
    game_field()
        :_gameField(), _zeroPos(15), _fieldChanged(true)
    {
        size_t i = 0;
        for(auto& item : _gameField)
        {
            item = static_cast<ubyte_t>(++i);
            if (item == 16)
            {
                item = 0;
            }
        }
        std::random_device rd;
        std::mt19937 g(rd());
        std::uniform_int_distribution<size_t> gen(0, 3);
        for(i = 0; i < 16*16; ++i)
        {
            directions dir = static_cast<directions>(gen(g));
            move(dir);
        }
    }

    void move(const directions& dir)
    {
        pos_t pos = pos_t::getFrom(_zeroPos);
        bool canMove = false;
        if (dir == directions::up && pos.row != 0)
        {
            --pos.row;
            canMove = true;
        }
        else if (dir == directions::down && pos.row != 3)
        {
            ++pos.row;
            canMove = true;
        }
        else if (dir == directions::left && pos.col != 0)
        {
            --pos.col;
            canMove = true;
        }
        else if (dir == directions::right && pos.col != 3)
        {
            ++pos.col;
            canMove = true;
        }
        if (canMove)
        {
            size_t newZeroPos = pos.toSizeT();
            std::swap(_gameField[_zeroPos], _gameField[newZeroPos]);
            _zeroPos = newZeroPos;
            _fieldChanged = true;
        }
    }

    void update()
    {
        _fieldChanged = false;
    }

    const bool& isFieldChanged()
    {
        return _fieldChanged;
    }

    void render(std::stringstream& ss)
    {
        drawLine(ss, 201, 203, 187);

        for(size_t i = 0; i < _gameField.size(); ++i)
        {
            ss << static_cast<char>(186u) << std::setfill(' ') << std::setw(3) << static_cast<short>(_gameField[i]);
            if ((i + 1) % 4 == 0)
            {
                ss << static_cast<char>(186u) << std::endl;
                if (i != _gameField.size() - 1)
                {
                    drawLine(ss, 204, 206, 185);
                }
            }
        }
        drawLine(ss, 200, 202, 188);
    }

    bool isGameCompleted()
    {
        bool bRet = true;

        for(ubyte_t i = 0; i < _gameField.size(); ++i)
        {
            if (i != 15)
            {
                if (i + 1 != _gameField[i])
                {
                    bRet = false;
                    break;
                }
            }
            else
            {
                if (_gameField[i] != 0)
                {
                    bRet = false;
                    break;
                }
            }
        }

        return bRet;
    }
};