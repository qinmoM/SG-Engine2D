#pragma once

#include "Map.h"
#include <raylib.h>
#include <iostream>

class Scene
{
private:
    Scene();
protected:
    Map* m_map;
public:
    ~Scene();
    // void isSuccess()
    // {
    //     std::cout << "Success" << std::endl;
    // }
    static Scene* create();
    void draw();
};