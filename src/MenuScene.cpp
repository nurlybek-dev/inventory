#include "MenuScene.h"
#include "SceneManager.h"

MenuScene::MenuScene() : Scene()
{
    mStartButton = new Button("Start", SCREEN_WIDTH/2-50, 200, 100, 50, 24);
    mExitButton = new Button("Exit", SCREEN_WIDTH/2-50, 300, 100, 50, 24);
}

MenuScene::~MenuScene()
{
    delete mStartButton;
    mStartButton = nullptr;
    
    delete mExitButton;
    mExitButton = nullptr;
}

void MenuScene::Update(float delta) 
{
    mStartButton->Update(delta);
    mExitButton->Update(delta);

    if(mStartButton->IsPressed())
    {
        SceneManager::Instance()->ChangeScene(GAME);
        return;
    }

    if(mExitButton->IsPressed())
    {
        // SceneManager::Instance()->ChangeScene(END);
        return;
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
