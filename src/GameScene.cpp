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
    mDeskTexture = new Texture("assets/Updated Paper Book/1 Sprites/Book Desk/4x2.png", 0, 0);
    mDeskTexture->SetPos(SCREEN_WIDTH/2 - mDeskTexture->Pos().w/2, 0);

    mMapOpenIcon = new Texture("assets/PNG/treasure-map.png", 102, SCREEN_HEIGHT-36);
    mMapCloseIcon = new Texture("assets/PNG/cancel.png", 800-30-4, 4);
    mMap = new Map();
    mWaitChoice = false;
    mIsMapOpen = false;
    mBook = new Book();
}
GameScene::~GameScene()
{
    delete mDeskTexture;
    mDeskTexture = nullptr;
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

    if(gDialogueManager->IsEnd()) {
        mBook->TheEnd();
    } else if(!mWaitChoice && mBook->IsOpen()) {
        int i=1;
        std::string text;
        switch (gDialogueManager->GetType())
        {
        case DialogueType::COMBAT:
        case DialogueType::STORY:
            if(mBook->IsAnimating()) {
                SDL_Log("Animating\n");
            }
            if(mBook->IsWaitNextPage()) {
                SDL_Log("IsWaitNextPage\n");
            }

            if(!mBook->IsAnimating() && !mBook->IsWaitNextPage()) {
                text = gDialogueManager->GetText();
                if(mBook->IsTextFit(text)) {
                    mBook->AddText(text);
                    gDialogueManager->Next();
                } else {
                    mBook->WaitNextPage();
                }
            }
            break;
        case DialogueType::CHOICE:
            text = gDialogueManager->GetText();
            mChoices.clear();
            for(auto& c : gDialogueManager->GetChoices())
            {
                text += "\n" + std::to_string(i) + ". " + c.text;
                i++;
            }
            if(mBook->IsTextFit(text)) {
                mBook->AddText(gDialogueManager->GetText());
                mChoices.clear();
                i = 1;
                for(auto& c : gDialogueManager->GetChoices())
                {
                    mBook->AddText("\n" + std::to_string(i) + ". " + c.text);
                    mChoices.push_back(c);
                    i++;
                }
                mWaitChoice = true;
            } else {
                mBook->NewPage();
            }
            break;
        case DialogueType::ABILITY_CHECK:
            break;
        case DialogueType::END:
            // if(!mBook->IsAnimating() && !mBook->IsWaitNextPage()) {
            //     text = gDialogueManager->GetText();
            //     if(mBook->IsTextFit(text)) {
            //         mBook->AddText(text);
            //         mBook->TheEnd();
            //     } else {
            //         mBook->WaitNextPage();
            //     }
            // }
            break;
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
    mDeskTexture->Render();
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
            if(sym >= SDLK_1 && sym <= SDLK_9 && sym - SDLK_1 <= mChoices.size() && !mBook->IsWaitNextPage() && !mBook->IsAnimating() && mBook->IsInLastPage()) {
                gDialogueManager->SelectChoice(sym - SDLK_1);
                mWaitChoice = false;

                if(!gDialogueManager->IsEnd()) {
                    mBook->NewPage();
                }
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