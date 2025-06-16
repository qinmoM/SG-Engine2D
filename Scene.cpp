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
    m_map->setPlayerSpeed(140);
    m_map->setPlayerDataManage();
    Player* player = m_map->getPlayer();
    player->DMS->setHP(10);
    m_map->setPlayerFlash();
    m_map->setPlayerFlashOn(true);
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
    Player* player = m_map->getPlayer();
    DrawRectangle(player->x, player->y, player->width, player->height, Color{ 55, 155, 55, 255 });
    // player flash

    if (player->flash->isObstructed)
    {
        //              Fanned player flash(unobstructed view)
        if (player->flash->on)
        {
            float px = player->flash->x;
            float py = player->flash->y;
            float x = 0;
            float y = 0;
            float angle = 0;
            float distance = player->flash->distance;
            float vicinity = player->flash->vicinity;
            for (int i = 0; i < player->flash->angleOfView * 2.0f; i++)
            {
                angle = player->flash->angle - player->flash->angleOfView / 2 + i / 2.0f;
                float xNear = px + vicinity * cos(angle * PI / 180.0f);
                float yNear = py + vicinity * sin(angle * PI / 180.0f);
                float x = px + distance * cos(angle * PI / 180.0f);
                float y = py + distance * sin(angle * PI / 180.0f);
                RaylibTools::DrawLine(xNear, yNear, x, y, 3, Color{ 255, 255, 255, 50 });
            }
        }
    }
    else
    {
        //              Fanned player flash(obstructed view)
        if (player->flash->on)
        {
            float px = player->flash->x;
            float py = player->flash->y;
            float x = 0;
            float y = 0;
            float angle = 0;
            int precision = player->flash->precision ? 1 : 4;
            float vicinity = player->flash->vicinity;
            for (int i = 0; i < player->flash->angleOfView * 2.0f; i++)
            {
                angle = player->flash->angle - player->flash->angleOfView / 2 + i / 2.0f;
                float xNear = px + vicinity * cos(angle * PI / 180.0f);
                float yNear = py + vicinity * sin(angle * PI / 180.0f);
                int temp = 0;
                bool isDraw = false;
                for (; temp < player->flash->distance; temp += precision)
                {
                    x = px + temp * cos(angle * PI / 180.0f);
                    y = py + temp * sin(angle * PI / 180.0f);
                    if (m_map->isCovered(x, y))
                    {
                        break;
                    }
                }
                isDraw = temp > vicinity ? true : false;
                if (isDraw)
                {
                    RaylibTools::DrawLine(xNear, yNear, x, y, 3, Color{ 255, 255, 255, 50 });
                }
            }
        }
    }

    //                  obstacles
    int all = m_map->numObstacles();
    for (int i = 0; i < all; i++)
    {
        Obstacle* obstacle = m_map->getObstacle(i);
        DrawRectangle(obstacle->x, obstacle->y, obstacle->width, obstacle->height, BLACK);
    }
}

void Scene::update(float delta)
{
    // player movement
    Player* player = m_map->getPlayer();
    float speed = player->speed;
    // buffer movement
    float moveX = 0;
    float moveY = 0;
    // check if player is diagonal movement
    bool up     =  IsKeyDown(KEY_UP)    ||  IsKeyDown(KEY_W);
    bool down   =  IsKeyDown(KEY_DOWN)  ||  IsKeyDown(KEY_S);
    bool left   =  IsKeyDown(KEY_LEFT)  ||  IsKeyDown(KEY_A);
    bool right  =  IsKeyDown(KEY_RIGHT) ||  IsKeyDown(KEY_D);
    bool isDiagonal = (up && right) || (up && left) || (down && right) || (down && left);
    if (up)
    {
        moveY -= isDiagonal ? speed * 0.7071f * delta : speed * delta;
    }
    if (down)
    {
        moveY += isDiagonal ? speed * 0.7071f * delta : speed * delta;
    }
    if (left)
    {
        moveX -= isDiagonal ? speed * 0.7071f * delta : speed * delta;
    }
    if (right)
    {
        moveX += isDiagonal ? speed * 0.7071f * delta : speed * delta;
    }
    // update player position
    bool xIsColliding = false;
    bool yIsColliding = false;
    if (moveX && !(xIsColliding = m_map->isColliding(player->x + moveX, player->y)))
    {
        player->x += yIsColliding ? moveX * 1.4142f : moveX;
    }
    if (moveY && !(yIsColliding = m_map->isColliding(player->x, player->y + moveY)))
    {
        player->y += xIsColliding ? moveY * 1.4142f : moveY;
    }

    // player flash
    Vector2 mousePos = GetMousePosition();
    if (player->flash)
    {
        player->flash->x = player->x + player->width / 2;
        player->flash->y = player->y + player->height / 2;
        if (mousePos.x && mousePos.y && !(mousePos.x == player->flash->x && mousePos.y == player->flash->y))
        {
            player->flash->angle = atan2(mousePos.y - player->flash->y, mousePos.x - player->flash->x) * 180.0f / PI;
        }
    }
}
