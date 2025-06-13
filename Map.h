#pragma once

#include <vector>

struct Obstacle
{
    int x;          // x coordinate of the obstacle
    int y;          // y coordinate of the obstacle
    int width;      // width of the obstacle
    int height;     // height of the obstacle
};

class Map
{
protected:
    std::vector<Obstacle*> obstacles;                       // list of obstacles in the map
public:
    Map();                                                  // constructor
    void addObstacle(Obstacle obstacle);                    // add an obstacle to the map  
    void addObstacle(int x, int y, int width, int height);  // add an obstacle to the map
    void removeObstacle(int index);                         // remove an obstacle from the map by index
    void clearObstacles();                                  // remove all obstacles from the map
    int numObstacles();                                     // get the number of obstacles in the map
    Obstacle* getObstacle(int index);                       // get an obstacle by index
};