#pragma once

#include <vector>
#include <cstdint>
#include <memory>
#include <functional>
#include <cmath>
#include "DataManage.h"

// a simple pixel image struct// different graphics libraries need to correspond program
struct PixelImage
{
    int id = 0;                                                 // id of the pixel image
    int size;                                                   // size of every pixel
    std::vector<std::vector<std::vector<uint8_t>>> pixels;      // image information
    int width;                                                  // the number of element width
    int height;                                                 // the number of element height
    int curr = 0;                                               // now pixel index

    PixelImage(int id, int size, std::vector<std::vector<std::vector<uint8_t>>> pixels, int width, int height)
        : id(id)
        , size(size)
        , pixels(pixels)
        , width(width)
        , height(height)
    { }
};

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

// Fallen object class
struct Object
{
    float x;                            // x coordinate of the object
    float y;                            // x coordinate of the object
    int width;                          // pixel width of the object
    int height;                         // pixel height of the object
    PixelImage* pixelImage = nullptr;   // pointer to the pixel image object

    //              Functions

    std::function<void(DataManage*)> dataFunc = nullptr;

    //              Constructor and Destructor

    Object(float x, float y, int w, int h, std::function<void(DataManage*)> dataFunc = nullptr)
        : x(x)
        , y(y)
        , width(w)
        , height(h)
        , dataFunc(dataFunc)
    { }

    Object(float x, float y, PixelImage* pixelImage, int w, int h, std::function<void(DataManage*)> dataFunc = nullptr)
        : x(x)
        , y(y)
        , width(w)
        , height(h)
        , pixelImage(pixelImage)
        , dataFunc(dataFunc)
    { }

    ~Object()
    {
        delete pixelImage;
    }

};

// player class
struct Player
{
    float x;                            // x coordinate of the player
    float y;                            // y coordinate of the player
    int width;                          // width on the interface
    int height;                         // height on the interface
    float speed = 0.0f;                 // speed of the player
    Flash* flash = nullptr;             // pointer to the flashlight object
    DataManage* DMS = nullptr;          // pointer to the data manage object
    PixelImage* pixelImage = nullptr;   // pointer to the pixel image object
};

// obstacle class
struct Obstacle
{
    float x;                            // x coordinate of the obstacle
    float y;                            // y coordinate of the obstacle
    int width;                          // width of the obstacle
    int height;                         // height of the obstacle
};

// moveble range class
struct Coverage
{
    float x;                            // x coordinate of the coverage
    float y;                            // y coordinate of the coverage
    int width;                          // width of the coverage
    int height;                         // height of the coverage

    Coverage(float x, float y, int w, int h)
        : x(x)
        , y(y)
        , width(w)
        , height(h)
    { }
};

class Map
{
protected:
    std::shared_ptr<Coverage> coverage = nullptr;               // movable range of the player
    std::vector<Obstacle*> obstacles;                           // list of obstacles in the map
    std::vector<std::shared_ptr<Object>> objects;               // list of objects in the map
    Player* player;                                             // player in the map
public:
    Map();                                                      // constructor
    virtual ~Map();                                             // destructor
    // player related functions
    void setPlayer(const Player& player);                       // set the player in the map
    void setPlayer(float x, float y, int w, int h);             // set the player in the map
    void setPlayerSpeed(float speed);                           // set the speed of the player in the map
    void setPlayerDataManage();                                 // set the dataManage of the player
    void setPlayerFlash();                                      // set the flashlight of the player in the map
    void setPlayerFlashOn(bool turn);                           // set the flashlight is on or off
    void setPlayerFlashView(float view, float angle = 0.0f);    // set the view range and the angle orientation
    void setPlayerFlashDist(float dist, float vici = 10.0f);    // set the view distance and vicinity
    void setPlayerFlashPrecision(bool turn);                    // set the precision is on or off
    void setPlayerPixelImage(int id, int size, std::vector<std::vector<std::vector<uint8_t>>> pixels, int width, int height);
                                                                // set the pixel image of the player
    Player* getPlayer();                                        // get the player in the map
    void clearPlayer();                                         // remove the player from the map
    void movePlayer(int dx, int dy);                            // move the player by dx and dy

    // movable range related functions
    void setCoverage(float x, float y, int w, int h);           // set the movable range of the player
    void clearCoverage();                                       // remove the movable range from the map

    // obstacle related functions
    void addObstacle(float x, float y, int w, int h);           // add an obstacle to the map
    void removeObstacle(size_t index);                          // remove an obstacle from the map by index
    void clearObstacles();                                      // remove all obstacles from the map
    int numObstacles();                                         // get the number of obstacles in the map
    Obstacle* getObstacle(size_t index);                        // get an obstacle by index
    void moveObstacle(size_t index, int dx, int dy);            // move an obstacle by index by dx and dy

    // object related functions
    void addObject(float x, float y, int id, int size, std::vector<std::vector<std::vector<uint8_t>>> pixels, int width, int height, std::function<void(DataManage*)> dataFunc = nullptr);
                                                                // add an object to the map
    void addObject(float x, float y, int w, int h, std::function<void(DataManage*)> dataFunc = nullptr);
                                                                // add an object to the map
    void removeObject(size_t index);                            // remove an object from the map by index
    void clearObjects();                                        // remove all objects from the map
    int numObjects();                                           // get the number of objects in the map
    std::shared_ptr<Object> getObject(size_t index);            // get an object by index
    void moveObject(size_t index, int dx, int dy);              // move an object by index by dx and dy

    // function related functions
    bool isCollidingCoverage(int x, int y);                                 // check the player is colliding with the movable range
    bool isCollidingObstacles(int x, int y);                                // check the player is colliding with any obstacle
    bool isCoveredObstacles(int x, int y);                                  // check the point is covered by any obstacle
    bool isCollidingObject(int index);                                      // check the player is colliding with any object

    bool isColliding(float x, float y, int w, int h, float dx, float dy, int dw, int dh);
                                                                            // check the rectangle is covered by any obstacle
    bool isCovered(float x, float y, int w, int h, float dx, float dy);     // check the rectangle is covered by any obstacle
    bool isCovered(float px, float py, float x, float y, float angleLeft, float angleRight, float vicinity, float distance);
                                                                            // check the point is covered by cone

};