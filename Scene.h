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
    Map* m_map;
    bool isCentered = false;
    float offsetX;
    float offsetY;
    std::vector<Color> colorPalette;
    void initColorPalette();
public:
    ~Scene();
    static Scene* create();
    void isPlayerCenter(bool is);
    void draw();
    void drawPixelImage(PixelImage* pixelImage, int x, int y);
    void update(float delta);

    void init1();

    void initMap1();
    void initPlayer1();
};