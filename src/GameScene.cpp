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

    mMapOpenIcon = new Texture("assets/PNG/treasure-map.png", 102, SCREEN_HEIGHT-36);
    mMapCloseIcon = new Texture("assets/PNG/cancel.png", 800-30-4, 4);
    mMap = new Map();
    mWaitChoice = false;
    mIsMapOpen = false;
    mBook = new Book();
}
GameScene::~GameScene()
{
    delete mBook;
    mBook = nullptr;
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
    delete mMapOpenIcon;
    mMapOpenIcon = nullptr;
    delete mMapCloseIcon;
    mMapCloseIcon = nullptr;
    delete mMap;
    mMap = nullptr;
}

void GameScene::Update(float delta)
{
    mBook->Update(delta);

    if(!mWaitChoice && mBook->IsOpen()) {
        if(gDialogueManager->IsEnd()) {
            mBook->TheEnd();
        }
        else {
            int i=1;
            switch (gDialogueManager->GetType())
            {
            case DialogueType::STORY:
                mBook->AddText(gDialogueManager->GetText());
                mBook->AddText("\n");
                gDialogueManager->Next();
                break;
            case DialogueType::CHOICE:
                mBook->AddText(gDialogueManager->GetText());
                mChoices.clear();
                for(auto& c : gDialogueManager->GetChoices())
                {
                    mBook->AddChoice(std::to_string(i) + ". " + c.text);
                    i++;
                    mChoices.push_back(c);
                }
                mBook->AddText("\n");
                mWaitChoice = true;
                break;
            case DialogueType::COMBAT:
            case DialogueType::ABILITY_CHECK:
                break;
            }
        }
    }

    // if(mIsMapOpen) {
    //     mMap->Update(delta);
    //     return;
    // }
    // if(gDialogueManager->IsEnd()) {
    //     SDL_Log("GAME OVER!");
    //     SceneManager::Instance()->ChangeScene(MENU);
    //     return;
    // }

    // gCharacter->Update(delta);
    // gDialogueManager->Update(delta);
}

void GameScene::Render()
{
    mBook->Render();
    // if(mIsMapOpen) {
    //     mMap->Render();
    //     mMapCloseIcon->Render();
    //     return;
    // }
    // gLeftPanel->Render();
    // gTopPanel->Render();
    // gBottomPanel->Render();
    // gMapPanel->Render();
    // gDialogueManager->Render();
    // gCharacter->Render();
    // mMapOpenIcon->Render();
}

void GameScene::Input(SDL_Event event)
{
    mBook->Input(event);

    int x = event.motion.x;
    int y = event.motion.y;

    if(mWaitChoice && mBook->IsOpen())
    {
        if(event.type == SDL_KEYDOWN)
        {
            auto sym = event.key.keysym.sym;
            if(sym >= SDLK_1 && sym <= SDLK_9 && sym - SDLK_1 <= mChoices.size() && !mBook->WaitNextPage() && !mBook->IsAnimating()) {
                SDL_Log("Choices: %d", sym - SDLK_1);
                gDialogueManager->SelectChoice(sym - SDLK_1);
                mWaitChoice = false;
                mBook->AddText("\n");
            }
        }
    }

    // if(mIsMapOpen) {
    //     SDL_Rect rect = mMapCloseIcon->Pos();
    //     if(event.type == SDL_MOUSEBUTTONUP && x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h)
    //     {
    //         CloseMap();
    //     }
    //     mMap->Input(event);
    //     return;
    // }

    // SDL_Rect rect = mMapOpenIcon->Pos();
    // if(event.type == SDL_MOUSEBUTTONUP && x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h)
    // {
    //     OpenMap();
    // }
    // gCharacter->Input(event);
    // gDialogueManager->Input(event);
}

void GameScene::OpenMap()
{
    mIsMapOpen = true;
}

void GameScene::CloseMap()
{
    mIsMapOpen = false;
}