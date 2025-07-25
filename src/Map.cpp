#include "../include/Map.h"

//              Map related functions

Map::Map()
{
    player = nullptr;
}

Map::~Map()
{
    if (player)
    {
        clearPlayer();
    }
    if (obstacles.size() > 0)
    {
        clearObstacles();
    }
    if (objects.size() > 0)
    {
        clearObjects();
    }
}

//              Player related functions

void Map::setPlayer(const Player& player)
{
    if (!this->player)
    {
        this->player = new Player(player);
    }
}

void Map::setPlayer(float x, float y, int w, int h)
{
    if (!this->player)
    {
        player = new Player{ x, y, w, h };
        setPlayerSpeed(0.0f);
    }
}

void Map::setPlayerSpeed(float speed)
{
    if (player)
    {
        player->speed = speed;
    }
}

void Map::setPlayerDataManage()
{
    if (player && !player->DMS)
    {
        player->DMS = DataManage::create();
    }
}

void Map::setPlayerFlash()
{
    if (player && !player->flash)
    {
        player->flash = new Flash();
    }
}

void Map::setPlayerFlashOn(bool turn)
{
    if (player && player->flash)
    {
        player->flash->on = turn;
    }
}

void Map::setPlayerFlashView(float view, float angle)
{
    if (player && player->flash)
    {
        player->flash->angleOfView = view;
        player->flash->angle = angle;
    }
}

void Map::setPlayerFlashDist(float dist, float vici)
{
    if (player && player->flash)
    {
        player->flash->distance = dist;
        player->flash->vicinity = vici;
    }
}

void Map::setPlayerFlashPrecision(bool turn)
{
    if (player && player->flash)
    {
        player->flash->precision = turn;
    }
}

void Map::setPlayerPixelImage(int id, int size, std::vector<std::vector<std::vector<uint8_t>>> pixels, int width, int height)
{
    if (player)
    {
        player->pixelImage = new PixelImage(id, size, pixels, width, height);
        player->width = width * size;
        player->height = height * size;
    }
}

Player* Map::getPlayer()
{
    if (!player)
    {
        return nullptr;
    }
    return player;
}

void Map::clearPlayer()
{
    if (player)
    {
        delete player->DMS;
        player->DMS = nullptr;
        delete player->flash;
        player->flash = nullptr;
        delete player->pixelImage;
        player->pixelImage = nullptr;
    }
    delete player;
    player = nullptr;
}

//              movable range related functions

void Map::setCoverage(float x, float y, int w, int h)
{
    coverage = std::shared_ptr<Coverage>(new Coverage(x, y, w, h));
}

//              Obstacle related functions

void Map::addObstacle(float x, float y, int w, int h)
{
    Obstacle* obstacle = new Obstacle{ x, y, w, h };
    obstacles.push_back(obstacle);
}

void Map::removeObstacle(size_t index)
{
    if (index < 0 || index >= obstacles.size())
    {
        return;
    }
    std::vector<Obstacle*>::iterator it = obstacles.begin() + index;
    delete *it;
    obstacles.erase(it);
}

void Map::clearObstacles()
{
    for (std::vector<Obstacle*>::iterator it = obstacles.begin(); it != obstacles.end(); ++it)
    {
        delete *it;
    }
    obstacles.clear();
}

int Map::numObstacles()
{
    return obstacles.size();
}

Obstacle* Map::getObstacle(size_t index)
{
    if (index < 0 || index >= obstacles.size())
    {
        return nullptr;
    }
    return obstacles[index];
}

void Map::moveObstacle(size_t index, int x, int y)
{
    if (index < 0 || index >= obstacles.size())
    {
        return;
    }
    Obstacle* obstacle = obstacles[index];
    obstacle->x = x;
    obstacle->y = y;
}

//              Object related functions

void Map::addObject(float x, float y, int id, int size, std::vector<std::vector<std::vector<uint8_t>>> pixels, int width, int height, std::function<void(DataManage*)> dataFunc)
{
    PixelImage* pixelImage = new PixelImage(id, size, pixels, width, height);
    objects.push_back(std::make_shared<Object>(x, y, pixelImage, width * size, height * size, dataFunc));
}

void Map::addObject(float x, float y, int w, int h, std::function<void(DataManage*)> dataFunc)
{
    objects.push_back(std::make_shared<Object>(x, y, w, h, dataFunc));
}

void Map::removeObject(size_t index)
{
    if (index < 0 || index >= objects.size())
    {
        return;
    }
    objects.erase(objects.begin() + index);
}

void Map::clearObjects()
{
    objects.clear();
}

int Map::numObjects()
{
    return objects.size();
}

std::shared_ptr<Object> Map::getObject(size_t index)
{
    if (index < 0 || index >= objects.size())
    {
        return nullptr;
    }
    return objects[index];
}

void Map::moveObject(size_t index, int x, int y)
{
    if (index < 0 || index >= objects.size())
    {
        return;
    }
    objects[index]->x = x;
    objects[index]->y = y;
}

//              Collision related functions

bool Map::isCollidingCoverage(int x, int y)
{
    if (x > coverage->x && x + player->width < coverage->x + coverage->width &&
        y > coverage->y && y + player->height < coverage->y + coverage->height)
    {
        return false;
    }
    return true;
}

bool Map::isCollidingObstacles(int x, int y)
{
    int pX1 = x;
    int pX2 = x + player->width;
    int pY1 = y;
    int pY2 = y + player->height;
    if (player)
    {
        for (std::vector<Obstacle*>::iterator it = obstacles.begin(); it != obstacles.end(); ++it)
        {
            int oX1 = (*it)->x;
            int oX2 = (*it)->x + (*it)->width;
            int oY1 = (*it)->y;
            int oY2 = (*it)->y + (*it)->height;
            // check based on the four corners of the player and the obstacle
            if ( pX1 <= oX2 && pX1 >= oX1 && pY1 <= oY2 && pY1 >= oY1 ||
                 pX2 <= oX2 && pX2 >= oX1 && pY1 <= oY2 && pY1 >= oY1 ||
                 pX1 <= oX2 && pX1 >= oX1 && pY2 <= oY2 && pY2 >= oY1 ||
                 pX2 <= oX2 && pX2 >= oX1 && pY2 <= oY2 && pY2 >= oY1 )
            {
                return true;
            }
            // check based on the four corners of the obstacle and the player
            if ( oX1 <= pX2 && oX1 >= pX1 && oY1 <= pY2 && oY1 >= pY1 ||
                 oX2 <= pX2 && oX2 >= pX1 && oY1 <= pY2 && oY1 >= pY1 ||
                 oX1 <= pX2 && oX1 >= pX1 && oY2 <= pY2 && oY2 >= pY1 ||
                 oX2 <= pX2 && oX2 >= pX1 && oY2 <= pY2 && oY2 >= pY1 )
            {
                return true;
            }
        }
    }
    return false;
}

bool Map::isCoveredObstacles(int x, int y)
{
    for (std::vector<Obstacle*>::iterator it = obstacles.begin(); it != obstacles.end(); ++it)
    {
        int oX1 = (*it)->x;
        int oX2 = (*it)->x + (*it)->width;
        int oY1 = (*it)->y;
        int oY2 = (*it)->y + (*it)->height;
        if (x >= oX1 && x <= oX2 && y >= oY1 && y <= oY2)
        {
            return true;
        }
    }
    return false;
}

bool Map::isCollidingObject(int index)
{
    if (index < 0 || index >= objects.size() || !player)
    {
        return false;
    }
    
    if (isColliding(objects[index]->x, objects[index]->y, objects[index]->width, objects[index]->height,
            player->x, player->y, player->width, player->height) ||
        isColliding(player->x, player->y, player->width, player->height,
            objects[index]->x, objects[index]->y, objects[index]->width, objects[index]->height))
    {
        return true;
    }
    return false;
}

bool Map::isColliding(float x, float y, int w, int h, float dx, float dy, int dw, int dh)
{
    if (x >= dx && x <= dx + dw && y >= dy && y <= dy + dh                  ||
        x >= dx && x <= dx + dw && y + h >= dy && y + h <= dy + dh          ||
        x + w >= dx && x + w <= dx + dw && y >= dy && y <= dy + dh          ||
        x + w >= dx && x + w <= dx + dw && y + h >= dy && y + h <= dy + dh  )
    {
        return true;
    }
    return false;
}

bool Map::isCovered(float x, float y, int w, int h, float dx, float dy)
{
    int tX1 = dx - x;
    int tX2 = dx - y;
    if (tX1 >= 0 && tX1 <= w && tX2 >= 0 && tX2 <= h)
    {
        return true;
    }
    return false;
}

bool Map::isCovered(float px, float py, float x, float y, float angleLeft, float angleRight, float vicinity, float distance)
{
    float dist = static_cast<float>(std::sqrt(static_cast<double>((px - x) * (px - x) + (py - y) * (py - y))));
    if (dist > distance || dist < vicinity)
    {
        return false;
    }

    float angle = std::atan2(y - py, x - px) * 180.0f / 3.1415926535f;
    float range = angleLeft - angleRight;
    angle -= angleRight;
    while (angle < 0.0f)
    {
        angle += 360.0f;
    }
    while (angle >= 360.0f)
    {
        angle -= 360.0f;
    }
    if (angle < 0.0f || angle > range)
    {
        return false;
    }
    return true;
}
