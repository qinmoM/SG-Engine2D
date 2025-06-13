#include "Scene.h"

Scene::Scene()
{
    m_map = new Map;
    // obstacles
    m_map->addObstacle(115, 115, 770, 20);
    m_map->addObstacle(115, 135, 20, 750);
    m_map->addObstacle(135, 865, 750, 20);
    m_map->addObstacle(865, 135, 20, 125);
    m_map->addObstacle(865, 365, 20, 500);
    m_map->addObstacle(135, 740, 375, 20);
    m_map->addObstacle(135, 615, 250, 20);
    m_map->addObstacle(240, 365, 20, 250);
    m_map->addObstacle(240, 240, 145, 20);
    m_map->addObstacle(365, 260, 20, 250);
    m_map->addObstacle(385, 490, 125, 20);
    m_map->addObstacle(490, 510, 20, 230);
    m_map->addObstacle(490, 135, 20, 250);
    m_map->addObstacle(510, 365, 125, 20);
    m_map->addObstacle(615, 240, 20, 125);
    m_map->addObstacle(615, 510, 20, 250);
    m_map->addObstacle(615, 490, 125, 20);
    m_map->addObstacle(740, 260, 20, 250);
    m_map->addObstacle(740, 240, 125, 20);
    m_map->addObstacle(740, 615, 20, 250);
    // player
    m_map->setPlayer(176, 678, 20, 20);
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