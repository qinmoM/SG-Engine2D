#pragma once

#include "RaylibTools.h"
#include <functional>
#include <memory>

class Button
{
public:
    static std::unique_ptr<Button> create(int x, int y, int width, int height);

    virtual ~Button() = default;

protected:
    int x;                  // x position of the button
    int y;                  // y position of the button
    int width;              // width of the button
    int height;             // height of the button

protected:
    std::function<bool()> way = nullptr;
    std::function<void()> event = nullptr;

private:
    Button(int x, int y, int width, int height);
    Button(int x, int y);

};