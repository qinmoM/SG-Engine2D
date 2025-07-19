#include "Scene.h"

Scene::Scene()
{
    // color palette
    initColorPalette();
    m_map = new Map;
    init1();
}

Scene::~Scene()
{
    delete m_map;
}

void Scene::initColorPalette()
{
    int index = 0;

    // opaques
    for (int r = 0; r < 5; r += 1)
    {
        for (int g = 0; g < 5; g += 1)
        {
            for (int b = 0; b < 5; b += 1)
            {
                colorPalette.push_back(Color {
                    static_cast<unsigned char>(r * 64 > 255 ? 255 : r * 64),
                    static_cast<unsigned char>(g * 64 > 255 ? 255 : g * 64),
                    static_cast<unsigned char>(b * 64 > 255 ? 255 : b * 64),
                    255
                });
                index++;
            }
        }
    }

    // transparents
    for (int r = 0; r < 5; r += 1)
    {
        for (int g = 0; g < 5; g += 1)
        {
            for (int b = 0; b < 5; b += 1)
            {
                colorPalette.push_back(Color{
                    static_cast<unsigned char>(r * 64 > 255 ? 255 : r * 64),
                    static_cast<unsigned char>(g * 64 > 255 ? 255 : g * 64),
                    static_cast<unsigned char>(b * 64 > 255 ? 255 : b * 64),
                    128
                });
                index++;
            }
        }
    }

    // default colors
    colorPalette.push_back(Color{0, 0, 0, 0});         // 完全透明
    colorPalette.push_back(Color{255, 0, 0, 255});     // 撞击红
    colorPalette.push_back(Color{0, 255, 255, 255});   // 青
    colorPalette.push_back(Color{255, 0, 255, 255});   // 紫
    colorPalette.push_back(Color{0, 255, 0, 255});     // 绿
    colorPalette.push_back(Color{255, 255, 0, 255});   // 黄
}

Scene* Scene::create()
{
    return new Scene();
}

void Scene::isPlayerCenter(bool is)
{
    isCentered = is;
    Player* player = m_map->getPlayer();
    if (is)
    {
        offsetX = GetScreenWidth() / 2 - player->x - player->width / 2;
        offsetY = GetScreenHeight() / 2 - player->y - player->height / 2;
    }
}

void Scene::draw()
{
    Player* player = m_map->getPlayer();

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
                RaylibTools::DrawLine(xNear + offsetX, yNear + offsetY, x + offsetX,
                    y + offsetY, 3, Color{ 255, 255, 255, 50 });
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
                    if (m_map->isCoveredObstacles(x, y))
                    {
                        break;
                    }
                }
                isDraw = temp > vicinity ? true : false;
                if (isDraw)
                {
                    RaylibTools::DrawLine(xNear + offsetX, yNear + offsetY, x + offsetX,
                        y + offsetY, 3, Color{ 255, 255, 255, 50 });
                }
            }
        }
    }

    //                  obstacles
    int all = m_map->numObstacles();
    for (int i = 0; i < all; i++)
    {
        Obstacle* obstacle = m_map->getObstacle(i);
        DrawRectangle(obstacle->x + offsetX, obstacle->y + offsetY,
            obstacle->width, obstacle->height, Color{ 50, 50, 50, 255 });
    }

    //                  objects
    int allObjects = m_map->numObjects();
    if (isShelf)
    {
        for (int i = 0; i < allObjects; i++)
        {
            std::shared_ptr<Object> object = m_map->getObject(i);
            if (m_map->isCovered(player->x + player->width / 2, player->y + player->height / 2,
                object->x + object->width / 2, object->y + object->height / 2,
                player->flash->angle + player->flash->angleOfView / 2,
                player->flash->angle - player->flash->angleOfView / 2,
                player->flash->vicinity, player->flash->distance) )
            {
                // TODO: 优化射线检测
                bool isDraw = true;
                float oX = object->x + object->width / 2;
                float oY = object->y + object->height / 2;
                float pX = player->x + player->width / 2;
                float pY = player->y + player->height / 2;
                float dist = static_cast<float>(std::sqrt(static_cast<double>((oX - pX) * (oX - pX) + (oY - pY) * (oY - pY))));
                for (int j = 0; j < dist; j += 2)
                {
                    if (m_map->isCoveredObstacles(pX + (oX - pX) / dist * j, pY + (oY - pY) / dist * j))
                    {
                        isDraw = false;
                        break;
                    }
                }
                if (isDraw)
                {
                    if (object->pixelImage)
                    {
                        drawPixelImage(object->pixelImage, object->x + offsetX, object->y + offsetY);
                    }
                    else
                    {
                        DrawRectangle(object->x + offsetX, object->y + offsetY,
                            object->width, object->height, Color{ 255, 255, 255, 255 });
                    }
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < allObjects; i++)
        {
            std::shared_ptr<Object> object = m_map->getObject(i);
            if (object->pixelImage)
            {
                drawPixelImage(object->pixelImage, object->x + offsetX, object->y + offsetY);
            }
            else
            {
                DrawRectangle(object->x + offsetX, object->y + offsetY,
                    object->width, object->height, Color{ 255, 255, 255, 255 });
            }
        }
    }

    //                  player
    if (!player->pixelImage)
    {
        DrawRectangle(player->x + offsetX, player->y + offsetY, player->width,
            player->height, Color{ 55, 155, 55, 255 });
    }
    else
    {
        drawPixelImage(player->pixelImage, player->x + offsetX, player->y + offsetY);
    }
}

void Scene::drawPixelImage(PixelImage* pixelImage, int x, int y)
{
    Color color;
    int size = pixelImage->size;
    for (int i = 0; i < pixelImage->height; i++)
    {
        for (int j = 0; j < pixelImage->width; j++)
        {
            uint8_t temp = pixelImage->pixels[0][i][j];
            if (250 != temp)
            {
                color = colorPalette[temp];
                DrawRectangle(x + j * size, y + i * size, size, size, color);
            }
        }
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
    if (moveX && !(xIsColliding = m_map->isCollidingObstacles(player->x + moveX, player->y)))
    {
        player->x += yIsColliding ? moveX * 1.4142f : moveX;
    }
    if (moveY && !(yIsColliding = m_map->isCollidingObstacles(player->x, player->y + moveY)))
    {
        player->y += xIsColliding ? moveY * 1.4142f : moveY;
    }

    // player flash
    Vector2 mousePos = GetMousePosition();
    if (player->flash)
    {
        player->flash->x = player->x + player->width / 2;
        player->flash->y = player->y + player->height / 2;
        if (isCentered)
        {
            if (mousePos.x && mousePos.y && !(mousePos.x == player->x && mousePos.y == player->y))
            {
                player->flash->angle = atan2(mousePos.y - GetScreenHeight() / 2,
                    mousePos.x - GetScreenWidth() / 2) * 180.0f / PI;
            }
        }
        else
        {
            if (mousePos.x && mousePos.y && !(mousePos.x == player->flash->x && mousePos.y == player->flash->y))
            {
                player->flash->angle = atan2(mousePos.y - player->flash->y,
                    mousePos.x - player->flash->x) * 180.0f / PI;
            }
        }
    }

    // camera
    if (isCentered)
    {
        offsetX = GetScreenWidth() / 2 - player->x - player->width / 2;
        offsetY = GetScreenHeight() / 2 - player->y - player->height / 2;
    }

    // objects
    int allObjects = m_map->numObjects();
    for (int i = 0; i < allObjects; i++)
    {
        if (m_map->isCollidingObject(i))
        {
            std::shared_ptr<Object> object = m_map->getObject(i);
            if (object->dataFunc && player->DMS)
            {
                object->dataFunc(player->DMS);
                std::cout << "HP" << player->DMS->getHP() << std::endl;
                m_map->removeObject(i);
            }
        }
    }
}

//                Scene initialization

void Scene::init1()
{
    isShelf = true;
    // obstacles
    initMap1();
    // player
    initPlayer1();
    // object
    initObject1();
    // camera
    isCentered = true;
}

void Scene::initMap1()
{
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
}

void Scene::initPlayer1()
{
    std::unique_ptr<RaylibPixelModel> temp(RaylibPixelModel::create());
    //RaylibPixelModel* temp = RaylibPixelModel::create();
    temp->setFuFu();

    // player
    m_map->setPlayer(176, 650, 20, 20);
    m_map->setPlayerSpeed(140);
    m_map->setPlayerDataManage();
    Player* player = m_map->getPlayer();
    player->DMS->setMaxHP(10);
    player->DMS->addHP(-9);
    m_map->setPlayerFlash();
    m_map->setPlayerFlashOn(true);
    m_map->setPlayerPixelImage(1, temp->PixelImage, temp->width, temp->height);
}

void Scene::initObject1()
{
    void (*func)(DataManage*) = [](DataManage* data) -> void {
        data->addHP(1);
    };
    std::unique_ptr<RaylibPixelModel> temp(RaylibPixelModel::create());
    temp->setHeart();
    m_map->addObject(170.0f, 560.0f, 3, temp->PixelImage, temp->width, temp->height, func);
    m_map->addObject(170.0f, 800.0f, 3, temp->PixelImage, temp->width, temp->height, func);
    m_map->addObject(800.0f, 800.0f, 3, temp->PixelImage, temp->width, temp->height, func);
    m_map->addObject(550.0f, 300.0f, 3, temp->PixelImage, temp->width, temp->height, func);
}
