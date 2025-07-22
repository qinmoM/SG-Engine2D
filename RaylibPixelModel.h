#pragma once

#include "Map.h"

class RaylibPixelModel
{
private:
    RaylibPixelModel();
public:
    std::vector<std::vector<std::vector<uint8_t>>> PixelImage;
    int width, height;
    int id = 0;
public:
    ~RaylibPixelModel();
    static RaylibPixelModel* create();
    
    //          character
    void setTest();
    void setFuFu();
    void setStudent();

    //           object
    void setHeart();

    //             key
    void setHomeKey1();
};