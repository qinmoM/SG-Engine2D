#pragma once

#include <vector>
#include "DataManage.h"

// flashlight class// different graphics libraries need to correspond program
struct Flash
{
    bool on = false;                    // whether the flashlight is on or off
    bool isObstructed = false;          // light pass through the obstacle or not
    bool precision = false;             // whether the flashlight is in precision mode or not
    float x;                            // x coordinate of the flashlight
    float y;                            // y coordinate of the flashlight
    float angle = 0.0f;                 // angle of the flashlight
    float angleOfView = 70.0f;          // angle of view of the flashlight
    float vicinity = 10.0f;             // intensity of the flashlight
    float distance = 400.0f;            // distance of the flashlight
};

// player class
struct Player
{
    float x;                            // x coordinate of the player
    float y;                            // y coordinate of the player
    int width;                          // width of the player
    int height;                         // height of the player
    float speed = 0.0f;                 // speed of the player
    Flash* flash = nullptr;             // pointer to the flashlight object
    DataManage* DMS = nullptr;          // pointer to the data manage object
};

// obstacle class
struct Obstacle
{
    float x;                            // x coordinate of the obstacle
    float y;                            // y coordinate of the obstacle
    int width;                          // width of the obstacle
    int height;                         // height of the obstacle
};

class Map
{
protected:
    std::vector<Obstacle*> obstacles;                           // list of obstacles in the map
    Player* player;                                             // player in the map
public:
    Map();                                                      // constructor
    ~Map();                                                     // destructor
    // player related functions
    void setPlayer(const Player& player);                       // set the player in the map
    void setPlayer(float x, float y, int w, int h);             // set the player in the map
    void setPlayerSpeed(float speed);                           // set the speed of the player in the map
    void setPlayerDataManage();                                 // set the dataManage of the player
    void setPlayerFlash();                                      // set the flashlight of the player in the map
    void setPlayerFlashOn(bool turn);                           // set the flashlight is on or off
    void setPlayerFlashView(float View, float angle = 0.0f);    // set the view range and the angle orientation
    void setPlayerFlashDist(float dist, float vici = 10.0f);    // set the view distance and vicinity
    void setPlayerFlashPrecision(bool turn);                    // set the precision is on or off
    Player* getPlayer();                                        // get the player in the map
    void clearPlayer();                                         // remove the player from the map
    void movePlayer(int dx, int dy);                            // move the player by dx and dy

    // obstacle related functions
    void addObstacle(Obstacle obstacle);                        // add an obstacle to the map  
    void addObstacle(float x, float y, int w, int h);           // add an obstacle to the map
    void removeObstacle(size_t index);                          // remove an obstacle from the map by index
    void clearObstacles();                                      // remove all obstacles from the map
    int numObstacles();                                         // get the number of obstacles in the map
    Obstacle* getObstacle(size_t index);                        // get an obstacle by index
    void moveObstacle(size_t index, int dx, int dy);            // move an obstacle by index by dx and dy

    // function related functions
    bool isColliding(int x, int y);                             // check the player is colliding with any obstacle
    bool isCovered(int x, int y);                               // check the point is covered by any obstacle
};