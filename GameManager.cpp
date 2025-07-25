#include "GameManager.h"

//      Creating functions

std::unique_ptr<GameManager> GameManager::create()
{
    return std::unique_ptr<GameManager>(new GameManager());
}

//      Basic functions

void GameManager::init()
{
    setMenu();
}

void GameManager::background()
{
    switch (m_state)
    {
    //      None
    case GameState::None:
        ClearBackground(Color{ 205, 205, 215, 255 });
        break;
    //      Menu
    case GameState::Menu:
        m_menu->background();
        break;

    //      Playing
    case GameState::Playing:
        m_scene->drawBackground();
        break;

    //      Paused
    case GameState::Paused:
        break;

    //      GameOver
    case GameState::GameOver:
        break;
    }

}

void GameManager::render()
{
    switch (m_state)
    {
    //      None
    case GameState::None:
        background();
        break;
    //      Menu
    case GameState::Menu:
        m_menu->draw();
        break;

    //      Playing
    case GameState::Playing:
        m_scene->draw();
        break;

    //      Paused
    case GameState::Paused:
        break;

    //      GameOver
    case GameState::GameOver:
        break;

    default:
        break;
    }
}

void GameManager::update(float delta)
{
    // update tasks
    while (!m_tasks.empty())
    {
        m_tasks.front()();
        m_tasks.pop();
    }

    // update state
    switch (m_state)
    {
    //      Menu
    case GameState::Menu:
        m_menu->update(delta);
        break;

    //      Playing
    case GameState::Playing:
        m_scene->update(delta);
        break;

    //      Paused
    case GameState::Paused:
        break;

    //      GameOver
    case GameState::GameOver:
        break;

    default:
        break;
    }
}

//      Special functions

void GameManager::setState(GameState state)
{
    switch (state)
    {
    //      Menu
    case GameState::Menu:
        if (nullptr == m_menu)
        {
            throw std::logic_error("Menu is not initialized.");
        }
        m_state = GameState::Menu;
        break;

    //      Playing
    case GameState::Playing:
        if (nullptr == m_scene)
        {
            throw std::logic_error("Scene is not initialized.");
        }
        m_state = GameState::Playing;
        break;

    //      Paused
    case GameState::Paused:
        m_state = GameState::Paused;
        break;

    //      GameOver
    case GameState::GameOver:
        m_state = GameState::GameOver;
        break;

    //      abnormal
    default:
        throw std::logic_error("Invalid state.");
        break;
    }
}

void GameManager::release(GameState state)
{
    if (m_resetter.find(state) == m_resetter.end())
    {
        throw std::logic_error("Invalid state. | GameManager::release()");
    }
    m_resetter.find(state)->second();
}

void GameManager::releaseOther(GameState state)
{
    for (const auto& [stateTemp, resetter] : m_resetter)
    {
        if (stateTemp != state)
        {
            resetter();
        }
    }
}

void GameManager::goBack()
{
    if (m_history.size() < 2)
    {
        throw std::logic_error("No history to go back. | GameManager::goBack()");
    }
    m_history.pop();
    if (m_changer.count(m_history.top()) == 0)
    {
        throw std::logic_error("Invalid state. | GameManager::goBack()");
    }
    m_changer[m_history.top()]();
}

void GameManager::goHome()
{
    if (m_history.empty())
    {
        throw std::logic_error("No history to go home. | GameManager::goHome()");
    }
    while (m_history.top() != GameState::Menu)
    {
        m_history.pop();
        if (m_history.empty())
        {
            throw std::logic_error("No history to go home. | GameManager::goHome()");
        }
    }
    m_history.pop();
    if (m_changer.count(GameState::Menu) == 0)
    {
        throw std::logic_error("Invalid state. | GameManager::goHome()");
    }
    m_changer[GameState::Menu]();
}

void GameManager::changeTo(GameState state)
{
    setState(state);
    m_history.push(state);

    // release resource
    m_tasks.push(
        [this, state]()
        {
            this->releaseOther(state);
        }
    );
}

//      Different UI interface functions

void GameManager::setScene()
{
    m_scene = Scene::create();
    m_scene->initPlayer1();
    m_scene->initRange1();
    m_scene->initButton1(*this);

    changeTo(GameState::Playing);
}

void GameManager::setMenu()
{
    m_menu = Menu::create();
    m_menu->init();
    m_menu->init1(*this);

    changeTo(GameState::Menu);
}

GameManager::~GameManager()
{
    ;
}

GameManager::GameManager()
    : m_state(GameState::None)
    , m_scene(nullptr)
{
    ;
}
