#pragma once

#include "Scene.h"
#include "State.h"

class GameManager
{
public:
    static std::unique_ptr<GameManager> create();

    void init();
    void render();
    void update(float delta);

public:
    ~GameManager();

private:
    GameManager();

private:
    GameState m_state = GameState::Menu;
    std::unique_ptr<Scene> m_scene = nullptr;

};
