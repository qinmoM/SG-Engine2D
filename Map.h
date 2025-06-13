#pragma once

#include <vector>

struct Player
{
    int x;                  // x coordinate of the player
    int y;                  // y coordinate of the player
    int width;              // width of the player
    int height;             // height of the player
    float speed = 0.0f;     // speed of the player
};


struct Obstacle
{
    int x;                  // x coordinate of the obstacle
    int y;                  // y coordinate of the obstacle
    int width;              // width of the obstacle
    int height;             // height of the obstacle
};

class Map
{
protected:
    std::vector<Obstacle*> obstacles;                       // list of obstacles in the map
    Player* player;                                         // player in the map
public:
    Map();                                                  // constructor
    ~Map();                                                 // destructor
    void setPlayer(Player player);                          // set the player in the map
    void setPlayer(int x, int y, int width, int height);    // set the player in the map
    void setPlayerSpeed(float speed);                       // set the speed of the player in the map
    Player* getPlayer();                                    // get the player in the map
    void clearPlayer();                                     // remove the player from the map
    void movePlayer(int dx, int dy);                        // move the player by dx and dy

    void addObstacle(Obstacle obstacle);                    // add an obstacle to the map  
    void addObstacle(int x, int y, int width, int height);  // add an obstacle to the map
    void removeObstacle(size_t index);                      // remove an obstacle from the map by index
    void clearObstacles();                                  // remove all obstacles from the map
    int numObstacles();                                     // get the number of obstacles in the map
    Obstacle* getObstacle(size_t index);                    // get an obstacle by index
    void moveObstacle(size_t index, int dx, int dy);        // move an obstacle by index by dx and dy

    bool isColliding(int x, int y);                         // check if the player is colliding with any obstacle
};