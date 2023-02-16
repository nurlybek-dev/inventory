#include "Header.h"
#include "RenderManager.h"

Header::Header(const std::string& text)
{
    mLeftRect = {0, 0, 32, 64};
    mRightRect = {0, 0, 32, 64};

    mLeftTexture = new Texture("assets/Paper Pack/SpriteSheet/0.png", mLeftRect, {992, 2304, 32, 64});
    mRightTexture = new Texture("assets/Paper Pack/SpriteSheet/0.png", mRightRect, {1120, 2304, 32, 64});

    SetText(text);
}

Header::~Header()
{
    delete mLeftTexture;
    mLeftTexture = nullptr;

    delete mRightTexture;
    mRightTexture = nullptr;

    for(int i=0; i<mMiddleTextures.size(); i++) {
        delete mMiddleTextures[i];
        mMiddleTextures[i] = nullptr;
    }
    mMiddleTextures.clear();
}

void Header::Render()
{
    mLeftTexture->Render();
    mRightTexture->Render();
    for(int i=0; i<mMiddleTextures.size(); i++) {
        mMiddleTextures[i]->Render();;
    }

    RenderManager::Instance()->RenderText(mText, mTextRect.x, mTextRect.y, 36);
}

void Header::SetText(const std::string& text)
{
    mText = text;

    int w = 32;
    int h = 64;

    for(int i=0; i<mMiddleTextures.size(); i++) {
        delete mMiddleTextures[i];
        mMiddleTextures[i] = nullptr;
    }
    mMiddleTextures.clear();

    mTextRect = RenderManager::Instance()->RenderText(mText, 0, 0, 36);
    int middleCount = mTextRect.w / w;
    middleCount += 2;
    for(int i=0; i<middleCount; i++) {
        mMiddleTextures.push_back(new Texture("assets/Paper Pack/SpriteSheet/0.png", {0, 0, w, h}, {1056, 2304, 32, 64}));
    }

    int dw = mLeftRect.w + mRightRect.w + middleCount * w;
    int x = SCREEN_WIDTH / 2 - dw / 2;
    int y = 50;

    mLeftRect.x = x;
    mLeftRect.y = y;

    int middleW = middleCount * w;

    mLeftTexture->SetPos(x, y);
    x += mLeftRect.w;
    mTextRect.x = x + middleW / 2 - mTextRect.w / 2;
    mTextRect.y = y + h / 2 - mTextRect.h / 2;
    for(int i=0; i<mMiddleTextures.size(); i++) {
        mMiddleTextures[i]->SetPos(x, y);
        x += w;
    }
    mRightRect.x = x;
    mRightRect.y = y;
    mRightTexture->SetPos(x, y);
}
