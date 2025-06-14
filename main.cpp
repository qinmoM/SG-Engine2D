#include <raylib.h>
#include <memory>
#include <ctime>
#include "Scene.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

int main()
{
    // Initialize the window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Map");
    // Init Audio device
    InitAudioDevice();
    // init data
    //Scene* scene = Scene::create();
    std::unique_ptr<Scene> scene(Scene::create());

    float timeLast = 0.0f;
    // Set the target FPS
    SetTargetFPS(60);
    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        // Update
        ClearBackground(BLACK);
        scene->draw();
        scene->update((clock() - timeLast) / (float)CLOCKS_PER_SEC);
        timeLast = clock();
        
        EndDrawing();
    }
    // Close the window and OpenGL context
    CloseWindow();
    // Close the audio device
    CloseAudioDevice();
    return 0;
}