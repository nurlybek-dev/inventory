#include "Button.h"
#include "RenderManager.h"

Button::Button(std::string text, int x, int y)
{
    mTexture = new Texture("assets/Inventory.png", {x, y, 100, 50}, {0, 0, 1, 1});
    mText = text;
    mIsPressed = false;
    mIsPressedPrevFrame = false;
}

Button::~Button()
{
    delete mTexture;
    mTexture = nullptr;
}

bool Button::IsPressed()
{
    return mIsPressed || mIsPressedPrevFrame;
}

void Button::Update()
{
    if(mIsPressed) SDL_Log("%s mIsPressed: %d\n", mText.c_str(), mIsPressed);
}

void Button::Render()
{
    mTexture->Render();
    SDL_Rect rect = mTexture->Pos();
    // TODO: Text position centered
    RenderManager::Instance()->RenderText(mText, rect.x, rect.y);
}

void Button::Input(SDL_Event event)
{
    if(mIsPressed) 
        mIsPressedPrevFrame = true;
    else
        mIsPressedPrevFrame = false;

    mIsPressed = false;
    int x = event.motion.x;
    int y = event.motion.y;

    SDL_Rect rect = mTexture->Pos();
    if(event.type == SDL_MOUSEBUTTONUP && x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h)
    {
        mIsPressed = true;
    }
}
