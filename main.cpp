#include <ctime>
#include "GameManager.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

int main()
{
    // Initialize the window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Map");
    // Init Audio device
    InitAudioDevice();
    // init data
    std::unique_ptr<GameManager> manager = GameManager::create();
    manager->init();

    float timeCurrent = 0.0f;
    float timeLast = 0.0f;
    // Set the target FPS
    SetTargetFPS(60);
    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
    
        // Update
        ClearBackground(Color{ 0, 0, 0, 255 });
        timeCurrent = clock() / 1000.0f;
        manager->update(timeCurrent - timeLast);
        timeLast = timeCurrent;

        // Render
        manager->render();
        
        EndDrawing();
    }
    // Close the window and OpenGL context
    CloseWindow();
    // Close the audio device
    CloseAudioDevice();
    return 0;
}