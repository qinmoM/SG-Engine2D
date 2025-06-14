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
public:
    ~Scene();
    static Scene* create();
    void draw();
    void update(float delta);
};