#pragma once

#include <functional>
#include <memory>
#include "Map.h"

class Button
{
public:
    int x;                                              // x position of the button
    int y;                                              // y position of the button
    int width;                                          // width of the button
    int height;                                         // height of the button

    bool shouldDelete = false;                          // flag to delete the button

    std::unique_ptr<PixelImage> image = nullptr;        // image of the button

public:
    std::function<bool(Button&)> way = nullptr;
    std::function<void()> event = nullptr;

public:
    //                  create method

    static std::unique_ptr<Button> create(int x, int y, int width, int height)
    {
        return std::unique_ptr<Button>(new Button(x, y, width, height));
    }

    static std::unique_ptr<Button> create(int x, int y, int width, int height,
        std::function<bool(Button&)> way, std::function<void()> event)
    {
        return std::unique_ptr<Button>(new Button(x, y, width, height, way, event));
    }

    void setImage(int id, int size, std::vector<std::vector<std::vector<uint8_t>>> pixels, int width, int height)
    {
        image = std::make_unique<PixelImage>(id, size, pixels, width, height);
    }

    //            default detection method

    bool isClicked(int mouseX, int mouseY) const
    {
        return mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height;
    }

    //            destructor

    virtual ~Button() = default;

protected:
    Button(int x, int y, int width, int height)
        : x(x)
        , y(y)
        , width(width)
        , height(height)
    { }

    Button(int x, int y, int width, int height, std::function<bool(Button&)> way, std::function<void()> event)
        : x(x)
        , y(y)
        , width(width)
        , height(height)
        , way(way)
        , event(event)
    { }

};