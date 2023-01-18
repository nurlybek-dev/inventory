#include "GameScene.h"
#include "SceneManager.h"

GameScene::GameScene()
{
    gCharacter = new Character();
    gLeftPanel = new Panel(200, SCREEN_HEIGHT);
    gTopPanel = new Panel(600, 350);
    gBottomPanel = new Panel(600, 250);
    gMapPanel = new Panel(200, 200);
    gDialogueManager = new DialogueManager();
    gLeftPanel->SetPos(0, 0);
    gTopPanel->SetPos(200, 0);
    gBottomPanel->SetPos(200, 350);
}

GameScene::~GameScene()
{
    delete gCharacter;
    gCharacter = nullptr;
    delete gLeftPanel;
    gLeftPanel = nullptr;
    delete gTopPanel;
    gTopPanel = nullptr;
    delete gBottomPanel;
    gBottomPanel = nullptr;
    delete gMapPanel;
    gMapPanel = nullptr;
    delete gDialogueManager;
    gDialogueManager = nullptr;
}

void GameScene::Update()
{
    if(gDialogueManager->IsEnd()) {
        SDL_Log("GAME OVER!");
        SceneManager::Instance()->ChangeScene(MENU);
        return;
    }

    gCharacter->Update();
    gDialogueManager->Update();
}

void GameScene::Render()
{
    gLeftPanel->Render();
    gTopPanel->Render();
    gBottomPanel->Render();
    gMapPanel->Render();
    gDialogueManager->Render();
    gCharacter->Render();
}

void GameScene::Input(SDL_Event event)
{
    gCharacter->Input(event);
    gDialogueManager->Input(event);
}
