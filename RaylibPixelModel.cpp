#include "RaylibPixelModel.h"

RaylibPixelModel::RaylibPixelModel()
{
    width = 0;
    height = 0;
}

RaylibPixelModel::~RaylibPixelModel()
{

}

RaylibPixelModel* RaylibPixelModel::create()
{
    return new RaylibPixelModel();
}

void RaylibPixelModel::setTest()
{
    // 
    PixelImage = { { { 250, 250, 5, 250, 250 },
                     { 250, 250, 5, 250, 250 },
                         { 5, 5, 5, 5, 5 },
                     { 250, 250, 5, 250, 250 },
                      { 250, 5, 250, 5, 250 } } };
    width = 5;
    height = 5;
}