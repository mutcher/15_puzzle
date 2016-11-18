#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <Windows.h>
#include "game_field.h"

class game
{
private:
    game_field _gameField;
    std::stringstream _ss;
    size_t _stepNumber;

private:
    void clearConsole()
    {
        system("cls");
    }

    inline bool isKeyDown(int key)
    {
        return GetAsyncKeyState(key) != 0;
    }

    bool update()
    {
        _gameField.update();
        if (isKeyDown(VK_UP))
        {
            _gameField.move(directions::up);
        }
        else if (isKeyDown(VK_DOWN))
        {
            _gameField.move(directions::down);
        }
        else if (isKeyDown(VK_LEFT))
        {
            _gameField.move(directions::left);
        }
        else if (isKeyDown(VK_RIGHT))
        {
            _gameField.move(directions::right);
        }
        if (_gameField.isFieldChanged())
        {
            ++_stepNumber;
        }

        return _gameField.isGameCompleted();
    }

    void render(const bool& bIsWin)
    {
        _ss.str("");
        if (_gameField.isFieldChanged())
        {
            clearConsole();
            drawStepNumber();
            _gameField.render(_ss);
            if (bIsWin)
            {
                drawWinLabel();
            }
            std::cout << _ss.str();
        }
    }

    void drawWinLabel()
    {
        _ss << std::endl;
        _ss << "You WIN!!" << std::endl;
        _ss << "Press enter to exit" << std::endl;
    }

    void drawStepNumber()
    {
        _ss << "Step: " << _stepNumber << std::endl;
    }

public:
    game()
        :_gameField(), _ss(), _stepNumber(0)
    {
    }

    void run()
    {
        bool completed = false;
        render(completed);
        while (true)
        {
            completed = update();
            render(completed);
            if (completed)
            {
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
};
