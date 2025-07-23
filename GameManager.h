#pragma once

#include "Scene.h"
#include "State.h"
#include "Menu.h"
#include <queue>
#include <map>

class GameManager
{
public:
    static std::unique_ptr<GameManager> create();

    void init();
    void background();
    void render();
    void update(float delta);

    void setState(GameState state);
    void releaseOther(GameState state);

    void setScene();
    void setMenu();

public:
    ~GameManager();

private:
    GameManager();

private:
    GameState                                   m_state     =   GameState::Menu;
    std::unique_ptr<Menu>                       m_menu      =   nullptr;
    std::unique_ptr<Scene>                      m_scene     =   nullptr;
    std::queue<std::function<void()>>           m_tasks;
    std::map<GameState, std::function<void()>>  m_resetter  =
    {
        { GameState::Menu,      [this]() -> void    { m_menu.reset();  } },
        { GameState::Playing,   [this]() -> void    { m_scene.reset(); } }
    };

};
