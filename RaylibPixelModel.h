#pragma once

#include "Map.h"

class RaylibPixelModel
{
private:
    RaylibPixelModel();
public:
    std::vector<std::vector<std::vector<uint8_t>>> PixelImage;
    int width, height;
public:
    ~RaylibPixelModel();
    static RaylibPixelModel* create();
    void setTest();
};