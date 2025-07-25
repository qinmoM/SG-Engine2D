#pragma once

class GameManager;

#include "Map.h"
#include "RaylibTools.h"
#include "RaylibPixelModel.h"
#include "Button.h"
#include <raylib.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include <memory>

class Scene
{
private:
    Scene();

protected:
    int model = 0;                                      // game model
    Map* m_map;                                         // map object
    bool isCentered = false;                            // is player centered or not
    bool isShelf = false;                               // is shelf object and NPC or not
    float offsetX;                                      // camera offset x
    float offsetY;                                      // camera offset y
    std::vector<Color> colorPalette;                    // color palette table
    std::vector<std::unique_ptr<Button>> buttons;       // button vector
    Vector2 mousePos;                                   // mouse position

    void initColorPalette();                            // function of initialize color palette table

public:
    virtual ~Scene();
    static std::unique_ptr<Scene> create();
    void isPlayerCenter(bool is);

    void draw();
    void drawBackground();
    void drawPlayer();
    void drawFlash();
    void drawObstacles();
    void drawObjects();
    void drawButtons();

    void drawPixelImage(PixelImage* pixelImage, int x, int y);

    void update(float delta);
    void mouseUpdate(float delta);
    void buttonUpdate();

    void init1();

    void initMap1();
    void initButton1(GameManager& gameManager);
    void initRange1();
    void initPlayer1();
    void initObject1();
    void mouseUpdate1(float delta);

};
