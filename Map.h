#pragma once

#include <vector>
#include "DataManage.h"

struct Player
{
    float x;                      // x coordinate of the player
    float y;                      // y coordinate of the player
    int width;                    // width of the player
    int height;                   // height of the player
    float speed = 0.0f;           // speed of the player
    DataManage* DMS = nullptr;    // pointer to the data manage object
};


struct Obstacle
{
    float x;                      // x coordinate of the obstacle
    float y;                      // y coordinate of the obstacle
    int width;                    // width of the obstacle
    int height;                   // height of the obstacle
};

class Map
{
protected:
    std::vector<Obstacle*> obstacles;                       // list of obstacles in the map
    Player* player;                                         // player in the map
public:
    Map();                                                  // constructor
    ~Map();                                                 // destructor
    void setPlayer(const Player& player);                   // set the player in the map
    void setPlayer(float x, float y, int w, int h);         // set the player in the map
    void setPlayerSpeed(float speed);                       // set the speed of the player in the map
    void setPlayerDataManage();                             // set the dataManage of the player
    Player* getPlayer();                                    // get the player in the map
    void clearPlayer();                                     // remove the player from the map
    void movePlayer(int dx, int dy);                        // move the player by dx and dy

    void addObstacle(Obstacle obstacle);                    // add an obstacle to the map  
    void addObstacle(float x, float y, int w, int h);       // add an obstacle to the map
    void removeObstacle(size_t index);                      // remove an obstacle from the map by index
    void clearObstacles();                                  // remove all obstacles from the map
    int numObstacles();                                     // get the number of obstacles in the map
    Obstacle* getObstacle(size_t index);                    // get an obstacle by index
    void moveObstacle(size_t index, int dx, int dy);        // move an obstacle by index by dx and dy

    bool isColliding(int x, int y);                         // check if the player is colliding with any obstacle
};