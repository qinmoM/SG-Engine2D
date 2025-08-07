#pragma once

#include "Map.h"
#include "RaylibTools.h"

class RaylibPixelModel
{
private:
    RaylibPixelModel();
public:
    std::vector<std::vector<std::vector<uint8_t>>> Image;
    int width, height;
    int id = 0;
public:
    ~RaylibPixelModel();
    static RaylibPixelModel* create();
    static void setColorList(std::vector<Color>& colorPalette);
    static void drawPixelImage(PixelImage* pixelImage, int x, int y);

    //          scene
    void setBed1();
    void setCupboard1();
    void setBedroom1();
    
    //          character
    void setTest();
    void setFuFu();
    void setStudent();

    //           object
    void setHeart();

    //             key
    void setHomeKey1();
    void setBackKey1();
};