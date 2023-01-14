#include "MenuScene.h"
#include "SceneManager.h"

MenuScene::MenuScene() : Scene()
{
    mStartButton = new Button("Start", SCREEN_WIDTH/2-50, 200);
    mExitButton = new Button("Exit", SCREEN_WIDTH/2-50, 300);
}

MenuScene::~MenuScene()
{
    delete mStartButton;
    mStartButton = nullptr;
    
    delete mExitButton;
    mExitButton = nullptr;
}

void MenuScene::Update()
{
    mStartButton->Update();
    mExitButton->Update();

    if(mStartButton->IsPressed())
    {
        SceneManager::Instance()->ChangeScene(GAME);
    }

    if(mExitButton->IsPressed())
    {
        SceneManager::Instance()->ChangeScene(END);
    }
}

void MenuScene::Render()
{
    RenderManager::Instance()->RenderText("MENU", SCREEN_WIDTH/2, 50);
    mStartButton->Render();
    mExitButton->Render();
}

void MenuScene::Input(SDL_Event event)
{
    mStartButton->Input(event);
    mExitButton->Input(event);
}
