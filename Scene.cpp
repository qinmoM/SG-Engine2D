#include "Scene.h"

Scene::Scene()
{
    m_map = new Map;
    m_map->addObstacle(10, 10, 100, 50);
    m_map->addObstacle(20, 20, 50, 100);
}

Scene::~Scene()
{
    delete m_map;
}

Scene* Scene::create()
{
    return new Scene();
}

void Scene::draw()
{
    int all = m_map->numObstacles();
    for (int i = 0; i < all; i++)
    {
        Obstacle* obstacle = m_map->getObstacle(i);
        DrawRectangleLines(obstacle->x, obstacle->y, obstacle->width, obstacle->height, BLACK);
    }
}