#include "Scene.h"

Scene::Scene()
{
    m_map = new Map;
    m_map->addObstacle(100, 100, 100, 10);
    m_map->addObstacle(200, 200, 10, 100);
    m_map->setPlayer(300, 200, 20, 20);
    m_map->setPlayerSpeed(3 / 0.0166f);
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
    Player* player = m_map->getPlayer();
    DrawRectangleLines(player->x, player->y, player->width, player->height, Color{ 55, 155, 55, 255 });
}

void Scene::update(float delta)
{
    // player movement
    Player* player = m_map->getPlayer();
    int speed = player->speed;
    // buffer movement
    int moveX = 0;
    int moveY = 0;
    // check if player is diagonal movement
    bool isDiagonal = (IsKeyDown(KEY_UP)   &&   IsKeyDown(KEY_RIGHT)  ||
                       IsKeyDown(KEY_UP)   &&   IsKeyDown(KEY_LEFT)   ||
                       IsKeyDown(KEY_DOWN) &&   IsKeyDown(KEY_RIGHT)  ||
                       IsKeyDown(KEY_DOWN) &&   IsKeyDown(KEY_LEFT)   ||
                       IsKeyDown(KEY_W)    &&   IsKeyDown(KEY_D)      ||
                       IsKeyDown(KEY_W)    &&   IsKeyDown(KEY_A)      ||
                       IsKeyDown(KEY_S)    &&   IsKeyDown(KEY_D)      ||
                       IsKeyDown(KEY_S)    &&   IsKeyDown(KEY_A)      );
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
    {
        moveY -= isDiagonal ? speed * delta * 0.7071f : speed * delta;
    }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
    {
        moveY += isDiagonal ? speed * delta * 0.7071f : speed * delta;
    }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    {
        moveX -= isDiagonal ? speed * delta * 0.7071f : speed * delta;
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    {
        moveX += isDiagonal ? speed * delta * 0.7071f : speed * delta;
    }
    // update player position
    if (!m_map->isColliding(player->x + moveX, player->y))
    {
        player->x += moveX;
    }
    if (!m_map->isColliding(player->x, player->y + moveY))
    {
        player->y += moveY;
    }
}