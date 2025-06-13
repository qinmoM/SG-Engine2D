#include <raylib.h>
#include <memory>
#include "Scene.h"

int main()
{
    // Initialize the window
    InitWindow(1280, 720, "Test");
    // Init Audio device
    InitAudioDevice();
    // init data
    //Scene* scene = Scene::create();
    std::unique_ptr<Scene> scene(Scene::create());

    // Set the target FPS
    SetTargetFPS(60);
    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        // Update
        ClearBackground(WHITE);
        scene->draw();
        
        EndDrawing();
    }
    // Close the window and OpenGL context
    CloseWindow();
    // Close the audio device
    CloseAudioDevice();
    return 0;
}