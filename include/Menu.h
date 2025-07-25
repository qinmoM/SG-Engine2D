#pragma once

class GameManager;

#include "Button.h"
#include "RaylibPixelModel.h"

class Menu
{
public:
    //      default
    static std::unique_ptr<Menu> create();

    void init();

    void background();

    void draw();
    void drawButtons();

    void update(float delta);
    void buttonUpdate();

    //      functions

    void addButton(std::unique_ptr<Button>&& button);
    void drawPixelModel(int x, int y, int widthCount, int heightCount,
        int size, const std::vector<std::vector<uint8_t>>& pixels);

    //      specific functions

    void init1(GameManager& gameManager);

protected:
    std::vector<std::unique_ptr<Button>> buttons;
    std::vector<Color> colorPalette;

private:
    Menu() = default;

};