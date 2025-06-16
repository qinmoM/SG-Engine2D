#pragma once

#include "Map.h"
#include "RaylibTools.h"
#include <raylib.h>
#include <iostream>
#include <ctime>
#include <cmath>

class Scene
{
private:
    Scene();
protected:
    Map* m_map;
    bool isCentered = false;
    float offsetX;
    float offsetY;
public:
    ~Scene();
    static Scene* create();
    void isPlayerCenter(bool is);
    void draw();
    void update(float delta);
};