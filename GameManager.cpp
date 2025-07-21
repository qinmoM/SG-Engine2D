#include "GameManager.h"

std::unique_ptr<GameManager> GameManager::create()
{
    return std::unique_ptr<GameManager>(new GameManager());
}

void GameManager::init()
{
    m_state = GameState::Playing;
    m_scene = Scene::create();

    // test code
    m_scene->initPlayer1();
    m_scene->initRange1();
}

void GameManager::render()
{
    switch (m_state)
    {
    //      Menu
    case GameState::Menu:
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
    switch (m_state)
    {
    //      Menu
    case GameState::Menu:
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

GameManager::~GameManager()
{
    ;
}

GameManager::GameManager()
    : m_state(GameState::Menu)
    , m_scene(nullptr)
{
    ;
}
