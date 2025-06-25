#include "Map.h"

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
}

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

void Map::setPlayerPixelImage(int size, std::vector<std::vector<std::vector<uint8_t>>> pixels, int width, int height)
{
    if (player)
    {
        player->pixelImage = new PixelImage{ size, pixels, width, height };
        player->width = width * size;
        player->height = height * size;
    }
}

Player* Map::getPlayer()
{
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

void Map::addObstacle(Obstacle obstacle)
{
    obstacles.push_back(&obstacle);
}

void Map::addObstacle(float x, float y, int w, int h)
{
    Obstacle* obstacle = new Obstacle{ x, y, w, h };
    obstacles.push_back(obstacle);
}

void Map::removeObstacle(size_t index)
{
    obstacles.erase(obstacles.begin() + index * sizeof(Obstacle*));
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

bool Map::isColliding(int x, int y)
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

bool Map::isCovered(int x, int y)
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
