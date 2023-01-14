#include "SceneManager.h"

SceneManager* SceneManager::sInstance = nullptr;

SceneManager* SceneManager::Instance()
{
    if(sInstance == nullptr)
        sInstance = new SceneManager();
    
    return sInstance;
}

void SceneManager::Release()
{
    delete sInstance;
    sInstance = nullptr;
}

SceneManager::SceneManager()
{
    ChangeScene(MENU);
}

SceneManager::~SceneManager()
{
    delete mCurrentScene;
    mCurrentScene = nullptr;
}

void SceneManager::ChangeScene(Scenes scene)
{
    switch (scene)
    {
    case MENU:
        mCurrentScene = new MenuScene();
        break;
    case GAME:
        mCurrentScene = new GameScene();
        break;
    case END:
        mCurrentScene = nullptr;
        break;
    }
}

void SceneManager::Render()
{
    mCurrentScene->Render();
}

void SceneManager::Update()
{
    mCurrentScene->Update();
}

void SceneManager::Input(SDL_Event event)
{
    mCurrentScene->Input(event);
}

bool SceneManager::EndScene()
{
    return mCurrentScene == nullptr;
}
