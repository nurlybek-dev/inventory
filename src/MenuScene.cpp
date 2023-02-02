#include "MenuScene.h"
#include "SceneManager.h"

MenuScene::MenuScene() : Scene()
{
    mStartButton = new Button("Start", SCREEN_WIDTH/2-50, 200, 100, 50, 24);
    mExitButton = new Button("Exit", SCREEN_WIDTH/2-50, 300, 100, 50, 24);
    // x = 823, y = 663
    int x = SCREEN_WIDTH / 2 - 767/2;
    int y = SCREEN_HEIGHT / 2 - 624/2;
    int w = 768;
    int h = 624;

    mBookState = BookState::CLOSED;
    mBookTab = BookTab::PROFILE;

    mBookTabTextures[BookTab::PROFILE] = new Texture("assets/Updated Paper Book/2 Sprite Sheet/Png/1.png", {x, y, w, h}, {880, 3648, w, h});
    mBookTabTextures[BookTab::STATUS] = new Texture("assets/Updated Paper Book/2 Sprite Sheet/Png/1.png", {x, y, w, h}, {1696, 3648, w, h});
    mBookTabTextures[BookTab::INVENTORY] = new Texture("assets/Updated Paper Book/2 Sprite Sheet/Png/1.png", {x, y, w, h}, {2512, 3648, w, h});
    mBookTabTextures[BookTab::QUESTS] = new Texture("assets/Updated Paper Book/2 Sprite Sheet/Png/1.png", {x, y, w, h}, {3328, 3648, w, h});
    mBookTabTextures[BookTab::SAVES] = new Texture("assets/Updated Paper Book/2 Sprite Sheet/Png/1.png", {x, y, w, h}, {64, 4368, w, h});
    mBookTabTextures[BookTab::SETTINGS] = new Texture("assets/Updated Paper Book/2 Sprite Sheet/Png/1.png", {x, y, w, h}, {880, 4368, w, h});

    mDeskTexture = new Texture("assets/Updated Paper Book/1 Sprites/Book Desk/4.png", {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}, {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT});
    mBookClosed = new Texture("assets/Updated Paper Book/2 Sprite Sheet/Png/1.png", {x, y, w, h}, {64, 48, w, h});
    mBookOpened = new Texture("assets/Updated Paper Book/2 Sprite Sheet/Png/1.png", {x, y, w, h}, {64, 3648, w, h});
    mBookOpen = new Animation("Book open", "assets/Updated Paper Book/2 Sprite Sheet/Png/1.png", {x, y, w, h}, {64, 48, w, h}, 5, 48, 0.3, false, false, false);
    mBookClose = new Animation("Book close", "assets/Updated Paper Book/2 Sprite Sheet/Png/1.png", {x, y, w, h}, {3328, 48, w, h}, 5, 48, 0.3, false, false, true);
    mFlipLeft = new Animation("Flip left", "assets/Updated Paper Book/2 Sprite Sheet/Png/1.png", {x, y, w, h}, {6592, 1488, w, h}, 9, 48, 0.6, false, false, true);
    mFlipRight = new Animation("Flip right", "assets/Updated Paper Book/2 Sprite Sheet/Png/1.png", {x, y, w, h}, {64, 1488, w, h}, 9, 48, 0.6, false, false, false);
}

MenuScene::~MenuScene()
{
    delete mBookTabTextures[BookTab::PROFILE];
    delete mBookTabTextures[BookTab::STATUS];
    delete mBookTabTextures[BookTab::INVENTORY];
    delete mBookTabTextures[BookTab::QUESTS];
    delete mBookTabTextures[BookTab::SAVES];
    delete mBookTabTextures[BookTab::SETTINGS];
    mBookTabTextures[BookTab::PROFILE] = nullptr;
    mBookTabTextures[BookTab::STATUS] = nullptr;
    mBookTabTextures[BookTab::INVENTORY] = nullptr;
    mBookTabTextures[BookTab::QUESTS] = nullptr;
    mBookTabTextures[BookTab::SAVES] = nullptr;
    mBookTabTextures[BookTab::SETTINGS] = nullptr;
    mBookTabTextures.clear();

    delete mDeskTexture;
    mDeskTexture = nullptr;

    delete mBookClosed;
    mBookClosed = nullptr;

    delete mBookOpened;
    mBookOpened = nullptr;

    delete mBookOpen;
    mBookOpen = nullptr;

    delete mBookClose;
    mBookClose = nullptr;

    delete mFlipLeft;
    mFlipLeft = nullptr;

    delete mFlipRight;
    mFlipRight = nullptr;

    delete mStartButton;
    mStartButton = nullptr;
    
    delete mExitButton;
    mExitButton = nullptr;
}

void MenuScene::Update(float delta) 
{

    switch(mBookState)
    {
        case BookState::CLOSED:
            // mBookClosed->Update(delta);
            break;
        case BookState::OPENED:
            // mBookOpened->Update(delta);
            break;
        case BookState::OPENING:
            mBookOpen->Update(delta);
            if(mBookOpen->End()) {
                mBookState = BookState::OPENED;
            }
            break;
        case BookState::CLOSING:
            mBookClose->Update(delta);
            if(mBookClose->End()) {
                mBookState = BookState::CLOSED;
            }
            break;
        case BookState::FLIPPING_LEFT:
            mFlipLeft->Update(delta);
            if(mFlipLeft->End()) {
                int prevTab = mBookTab;
                mBookTab = static_cast<BookTab>(prevTab - 1);
                mBookState = BookState::OPENED;
            }
            break;
        case BookState::FLIPPING_RIGHT:
            mFlipRight->Update(delta);
            if(mFlipRight->End()) {
                int nextTab = mBookTab;
                mBookTab = static_cast<BookTab>(nextTab + 1);
                mBookState = BookState::OPENED;
            }
            break;
    }

    mStartButton->Update(delta);
    mExitButton->Update(delta);

    if(mStartButton->IsPressed())
    {
        SceneManager::Instance()->ChangeScene(GAME);
        return;
    }

    if(mExitButton->IsPressed())
    {
        SceneManager::Instance()->ChangeScene(END);
        return;
    }
}

void MenuScene::Render()
{
    RenderManager::Instance()->RenderText("MENU", SCREEN_WIDTH/2, 50);
    mStartButton->Render();
    mExitButton->Render();
    mDeskTexture->Render();
    switch(mBookState)
    {
        case BookState::CLOSED:
            mBookClosed->Render();
            break;
        case BookState::OPENED:
            mBookTabTextures[mBookTab]->Render();
            // mBookOpened->Render();
            break;
        case BookState::OPENING:
            mBookOpen->Render();
            break;
        case BookState::CLOSING:
            mBookClose->Render();
            break;
        case BookState::FLIPPING_LEFT:
            mFlipLeft->Render();
            break;
        case BookState::FLIPPING_RIGHT:
            mFlipRight->Render();
            break;
    }
}

void MenuScene::Input(SDL_Event event)
{
    mStartButton->Input(event);
    mExitButton->Input(event);

    switch(mBookState)
    {
        case BookState::CLOSED:
            // mBookClosed->Input(event);
            break;
        case BookState::OPENED:
            // mBookOpened->Input(event);
            break;
        case BookState::OPENING:
            mBookOpen->Input(event);
            break;
        case BookState::CLOSING:
            mBookClose->Input(event);
            break;
        case BookState::FLIPPING_LEFT:
            mFlipLeft->Input(event);
            break;
        case BookState::FLIPPING_RIGHT:
            mFlipRight->Input(event);
            break;
    }

    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_w:
                if(mBookState == BookState::CLOSED)
                {
                    mBookOpen->Play();
                    mBookState = BookState::OPENING;
                }
                break;
            case SDLK_s:
                if(mBookState == BookState::OPENED)
                {
                    mBookClose->Play();
                    mBookState = BookState::CLOSING;
                }
                break;
            case SDLK_a:
                if(mBookState == BookState::OPENED && mBookTab != BookTab::PROFILE)
                {
                    mFlipLeft->Play();
                    mBookState = BookState::FLIPPING_LEFT;
                }
                break;
            case SDLK_d:
                if(mBookState == BookState::OPENED && mBookTab != BookTab::SETTINGS)
                {
                    mFlipRight->Play();
                    mBookState = BookState::FLIPPING_RIGHT;
                }
                break;
        }
    }
}
