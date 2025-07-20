#pragma once

#include "Map.h"
#include "RaylibTools.h"
#include "RaylibPixelModel.h"
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
    int model = 0;                      // game model
    Map* m_map;                         // map object
    bool isCentered = false;            // is player centered or not
    bool isShelf = false;               // is shelf object and NPC or not
    float offsetX;                      // camera offset x
    float offsetY;                      // camera offset y
    std::vector<Color> colorPalette;    // color palette table
    Vector2 mousePos;                   // mouse position

    void initColorPalette();            // function of initialize color palette table

public:
    virtual ~Scene();
    static std::unique_ptr<Scene> create();
    void isPlayerCenter(bool is);
    void draw();
    void drawPixelImage(PixelImage* pixelImage, int x, int y);
    void update(float delta);
    void mouseUpdata(float delta);

    void init1();

    void initMap1();
    void initPlayer1();
    void initObject1();
    void mouseUpdata1(float delta);

};
