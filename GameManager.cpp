#include "GameManager.h"

std::unique_ptr<GameManager> GameManager::create()
{
    return std::unique_ptr<GameManager>(new GameManager());
}

void GameManager::init()
{
    m_menu = Menu::create();
    m_menu->init();
    setState(GameState::Menu);

    // test code
    m_menu->init1(*this);

    // m_scene = Scene::create();

    // // test code
    // m_scene->initPlayer1();
    // m_scene->initRange1();
    // m_scene->initButton1();

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

void GameManager::setState(GameState state)
{
    switch (state)
    {
    //      None
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

void GameManager::setScene()
{
    m_scene = Scene::create();
    m_scene->initPlayer1();
    m_scene->initRange1();
    m_scene->initButton1(*this);
    setState(GameState::Playing);

    // release resource
    m_tasks.push(
        [this]()
        {
            this->releaseOther(GameState::Playing);
        }
    );
}

void GameManager::setMenu()
{
    m_menu = Menu::create();
    m_menu->init();
    m_menu->init1(*this);
    setState(GameState::Menu);

    // release resource
    m_tasks.push(
        [this]()
        {
            this->releaseOther(GameState::Menu);
        }
    );
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
