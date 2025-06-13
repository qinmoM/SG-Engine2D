#include "Map.h"

Map::Map()
{
    
}

void Map::addObstacle(Obstacle obstacle)
{
    obstacles.push_back(&obstacle);
}

void Map::addObstacle(int x, int y, int width, int height)
{
    Obstacle* obstacle = new Obstacle{ x, y, width, height };
    obstacles.push_back(obstacle);
}

void Map::removeObstacle(int index)
{
    obstacles.erase(obstacles.begin() + index * sizeof(Obstacle*));
}

void Map::clearObstacles()
{
    obstacles.clear();
}

int Map::numObstacles()
{
    return obstacles.size();
}

Obstacle* Map::getObstacle(int index)
{
    if (index < 0 || index >= obstacles.size())
    {
        return nullptr;
    }
    return obstacles[index];
}