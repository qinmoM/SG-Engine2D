#pragma once

#include "Scene.h"
#include "State.h"
#include "Menu.h"
#include <queue>
#include <stack>
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
    void release(GameState state);
    void releaseOther(GameState state);
    void goBack();
    void goHome();
    void changeTo(GameState state);

    void setScene();
    void setMenu();

public:
    ~GameManager();

private:
    GameManager();

private:
    GameState                                   m_state     =   GameState::None;    // current state
    std::unique_ptr<Menu>                       m_menu      =   nullptr;            // current menu
    std::unique_ptr<Scene>                      m_scene     =   nullptr;            // current scene
    std::queue<std::function<void()>>           m_tasks;                            // list of tasks to be completed
    std::map<GameState, std::function<void()>>  m_resetter  =                       // map of reset functions
    {
        { GameState::Menu,      [this]() -> void    { m_menu.reset();  } },
        { GameState::Playing,   [this]() -> void    { m_scene.reset(); } }
    };
    std::map<GameState, std::function<void()>>  m_changer   =                       // map of change functions
    {
        { GameState::Menu,      [this]() -> void    { setMenu(); } },
        { GameState::Playing,   [this]() -> void    { setScene(); } }
    };
    std::stack<GameState>                       m_history;                          // history of states

};
