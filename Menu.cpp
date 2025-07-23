#include "Menu.h"
#include "GameManager.h"

std::unique_ptr<Menu> Menu::create()
{
    return std::unique_ptr<Menu>(new Menu());
}

void Menu::init()
{
    RaylibPixelModel::setColorList(colorPalette);
}

void Menu::background()
{
    ClearBackground(Color{ 165, 145, 125, 255 });
}

void Menu::draw()
{
    //  buttons
    drawButtons();

}

void Menu::drawButtons()
{
    for (std::unique_ptr<Button>& button : buttons)
    {
        if (button->image)
        {
            drawPixelModel(button->x, button->y, button->image->width, button->image->height,
                button->image->size, button->image->pixels[0]);
        }
        else
        {
            DrawRectangle(button->x, button->y, button->width, button->height, Color{ 200, 160, 210, 255 });
        }
    }
}

void Menu::update(float delta)
{
    //  buttons
    buttonUpdate();
}

void Menu::buttonUpdate()
{
    for (std::unique_ptr<Button>& button : buttons)
    {
        if (button->way && button->way(*button))
        {
            button->event();
        }
    }
}

//                  functions

void Menu::addButton(std::unique_ptr<Button>&& button)
{
    buttons.push_back(std::move(button));
}

void Menu::drawPixelModel(int x, int y, int widthCount, int heightCount,
        int size, const std::vector<std::vector<uint8_t>>& pixels)
{
    Color color;
    for (int i = 0; i < heightCount; i++)
    {
        for (int j = 0; j < widthCount; j++)
        {
            uint8_t temp = pixels[i][j];
            if (250 != temp)
            {
                color = colorPalette[temp];
                DrawRectangle(x + j * size, y + i * size, size, size, color);
            }
        }
    }
}

void Menu::init1(GameManager& gameManager)
{
    // std::unique_ptr<RaylibPixelModel> temp;
    // temp->setHomeKey1();
    addButton(Button::create(500, 400, 500, 200,
        [](Button& button) -> bool
        {
            Vector2 mousePos = GetMousePosition();
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && button.isClicked(mousePos.x, mousePos.y))
            {
                return true;
            }
            return false;
        },
        [&gameManager]() -> void
        {
            gameManager.setScene();
        })
    );
    addButton(Button::create(500, 700, 500, 200,
        [](Button& button) -> bool
        {
            Vector2 mousePos = GetMousePosition();
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && button.isClicked(mousePos.x, mousePos.y))
            {
                return true;
            }
            return false;
        }, 
        [&gameManager]() -> void
        {
            exit(0);
        })
    );
}
