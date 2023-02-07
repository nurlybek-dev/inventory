#include "Book.h"

Book::Book()
{
    mWordsPerPage = 90;
    mCharsPerPage = 400;

    mLeftPage = {85+270, 110+140, 280*2, 16*2};
    mRightPage = {415+600, 110+140, 280*2, 16*2};

    mCurrentPage = 0;
    mPageCount = 0;

    mLeftPageWords = 0;
    mRightPageWords = 0;

    mLeftAnimatedText = new AnimatedText("", mLeftPage.x, mLeftPage.y, mLeftPage.w, mLeftPage.h);
    mRightAnimatedText = new AnimatedText("", mRightPage.x, mRightPage.y, mRightPage.w, mRightPage.h);

    mIsWritingToLeft = true;
    mWaitNextPage = false;
    mEnd = false;

    // x = 823, y = 663
    int x = SCREEN_WIDTH / 2 - 768*2/2;
    int y = SCREEN_HEIGHT / 2 - 624*2/2 - 50;
    int w = 768*2;
    int h = 624*2;

    mBookState = BookState::CLOSED;
    mNextTab = BookTab::STORY;
    mBookTab = BookTab::STORY;

    // mBookTabTextures[BookTab::STORY] = new Texture("assets/Updated Paper Book/2 Sprite Sheet/Png/1.png", {x, y, w, h}, {64, 3648, w, h});
    // mBookTabTextures[BookTab::PROFILE] = new Texture("assets/Updated Paper Book/2 Sprite Sheet/Png/1.png", {x, y, w, h}, {880, 3648, w, h});
    // mBookTabTextures[BookTab::STATUS] = new Texture("assets/Updated Paper Book/2 Sprite Sheet/Png/1.png", {x, y, w, h}, {1696, 3648, w, h});
    // mBookTabTextures[BookTab::INVENTORY] = new Texture("assets/Updated Paper Book/2 Sprite Sheet/Png/1.png", {x, y, w, h}, {2512, 3648, w, h});
    // mBookTabTextures[BookTab::QUESTS] = new Texture("assets/Updated Paper Book/2 Sprite Sheet/Png/1.png", {x, y, w, h}, {3328, 3648, w, h});
    // mBookTabTextures[BookTab::SAVES] = new Texture("assets/Updated Paper Book/2 Sprite Sheet/Png/1.png", {x, y, w, h}, {64, 4368, w, h});
    // mBookTabTextures[BookTab::SETTINGS] = new Texture("assets/Updated Paper Book/2 Sprite Sheet/Png/1.png", {x, y, w, h}, {880, 4368, w, h});

    // mBookClosed = new Texture("assets/Updated Paper Book/2 Sprite Sheet/Png/1.png", {x, y, w, h}, {64, 48, w, h});
    // mBookOpened = new Texture("assets/Updated Paper Book/2 Sprite Sheet/Png/1.png", {x, y, w, h}, {64, 3648, w, h});
    // mBookOpen = new Animation("Book open", "assets/Updated Paper Book/2 Sprite Sheet/Png/1.png", {x, y, w, h}, {64, 48, w, h}, 5, 48, 0.3, false, false, false);
    // mBookClose = new Animation("Book close", "assets/Updated Paper Book/2 Sprite Sheet/Png/1.png", {x, y, w, h}, {3328, 48, w, h}, 5, 48, 0.3, false, false, true);
    // mFlipLeft = new Animation("Flip left", "assets/Updated Paper Book/2 Sprite Sheet/Png/1.png", {x, y, w, h}, {6592, 1488, w, h}, 9, 48, 0.6, false, false, true);
    // mFlipRight = new Animation("Flip right", "assets/Updated Paper Book/2 Sprite Sheet/Png/1.png", {x, y, w, h}, {64, 1488, w, h}, 9, 48, 0.6, false, false, false);


    mBookTabTextures[BookTab::STORY] = new Texture("assets/Updated Paper Book/2 Sprite Sheet/Png/1x2.png", {x, y, w, h}, {128, 7296, w, h});
    mBookTabTextures[BookTab::PROFILE] = new Texture("assets/Updated Paper Book/2 Sprite Sheet/Png/1x2.png", {x, y, w, h}, {880*2, 3648*2, w, h});
    mBookTabTextures[BookTab::STATUS] = new Texture("assets/Updated Paper Book/2 Sprite Sheet/Png/1x2.png", {x, y, w, h}, {1696*2, 3648*2, w, h});
    mBookTabTextures[BookTab::INVENTORY] = new Texture("assets/Updated Paper Book/2 Sprite Sheet/Png/1x2.png", {x, y, w, h}, {2512*2, 3648*2, w, h});
    mBookTabTextures[BookTab::QUESTS] = new Texture("assets/Updated Paper Book/2 Sprite Sheet/Png/1x2.png", {x, y, w, h}, {3328*2, 3648*2, w, h});
    mBookTabTextures[BookTab::SAVES] = new Texture("assets/Updated Paper Book/2 Sprite Sheet/Png/1x2.png", {x, y, w, h}, {64*2, 4368*2, w, h});
    mBookTabTextures[BookTab::SETTINGS] = new Texture("assets/Updated Paper Book/2 Sprite Sheet/Png/1x2.png", {x, y, w, h}, {880*2, 4368*2, w, h});

    mBookClosed = new Texture("assets/Updated Paper Book/2 Sprite Sheet/Png/1x2.png", {x, y, w, h}, {64*2, 48*2, w, h});
    mBookOpened = new Texture("assets/Updated Paper Book/2 Sprite Sheet/Png/1x2.png", {x, y, w, h}, {64*2, 3648*2, w, h});
    mBookOpen = new Animation("Book open", "assets/Updated Paper Book/2 Sprite Sheet/Png/1x2.png", {x, y, w, h}, {64*2, 48*2, w, h}, 5, 48*2, 0.3, false, false, false);
    mBookClose = new Animation("Book close", "assets/Updated Paper Book/2 Sprite Sheet/Png/1x2.png", {x, y, w, h}, {3328*2, 48*2, w, h}, 5, 48*2, 0.3, false, false, true);
    mFlipLeft = new Animation("Flip left", "assets/Updated Paper Book/2 Sprite Sheet/Png/1x2.png", {x, y, w, h}, {6592*2, 1488*2, w, h}, 9, 48*2, 0.6, false, false, true);
    mFlipRight = new Animation("Flip right", "assets/Updated Paper Book/2 Sprite Sheet/Png/1x2.png", {x, y, w, h}, {64*2, 1488*2, w, h}, 9, 48*2, 0.6, false, false, false);


    NewPage();
}

Book::~Book()
{
    delete mBookTabTextures[BookTab::STORY];
    delete mBookTabTextures[BookTab::PROFILE];
    delete mBookTabTextures[BookTab::STATUS];
    delete mBookTabTextures[BookTab::INVENTORY];
    delete mBookTabTextures[BookTab::QUESTS];
    delete mBookTabTextures[BookTab::SAVES];
    delete mBookTabTextures[BookTab::SETTINGS];
    mBookTabTextures[BookTab::STORY] = nullptr;
    mBookTabTextures[BookTab::PROFILE] = nullptr;
    mBookTabTextures[BookTab::STATUS] = nullptr;
    mBookTabTextures[BookTab::INVENTORY] = nullptr;
    mBookTabTextures[BookTab::QUESTS] = nullptr;
    mBookTabTextures[BookTab::SAVES] = nullptr;
    mBookTabTextures[BookTab::SETTINGS] = nullptr;
    mBookTabTextures.clear();

    delete mLeftAnimatedText;
    mLeftAnimatedText = nullptr;

    delete mRightAnimatedText;
    mRightAnimatedText = nullptr;

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

}

void Book::OpenTab(BookTab tab)
{
    if(mBookState != BookState::CLOSED && mBookState != BookState::CLOSING && mBookState != BookState::OPENING && mBookState == BookState::OPENED && mBookTab != tab)
    {
        mNextTab = tab;
        if(mBookTab > tab)
        {
            FlipLeft();
        }
        else
        {
            FlipRight();
        }
    }
}

bool Book::IsTextFit(const std::string& text)
{
    std::vector<std::string> words;
    size_t count = Split(text, words, ' ');

    int forLeft = mWordsPerPage - mLeftPageWords;
    int forRight = mWordsPerPage - mRightPageWords;

    return forLeft > count || forRight > count;
}

void Book::AddText(std::string text)
{
    if(mLeftPageWords > 0) text = "\n" + text;
    std::vector<std::string> words;
    size_t count = Split(text, words, ' ');

    int forLeft = mWordsPerPage - mLeftPageWords;
    int forRight = mWordsPerPage - mRightPageWords;

    std::string leftText = "";
    std::string rightText = "";

    if(mIsWritingToLeft && forLeft >= count) {
        for(int i=0; i < count; i++) {
            leftText += words[i] + ' ';
            mLeftPageWords++;
        }
        mPages[mCurrentPage].leftPageText += leftText;
        mLeftAnimatedText->AddText(leftText);
    } else if(forRight >= count) {
        mIsWritingToLeft = false;
        for(int i=0; i < count; i++) {
            rightText += words[i] + ' ';
            mRightPageWords++;
        }
        mPages[mCurrentPage].rightPageText += rightText;
        mRightAnimatedText->AddText(rightText);
    } else {
        mWaitNextPage = true;
    }
}

void Book::NewPage()
{
    if(!mEnd) {
        SDL_Log("New Page\n");
        mLeftPageWords = 0;
        mRightPageWords = 0;
        mLeftAnimatedText->Clear();
        mRightAnimatedText->Clear();
        mIsWritingToLeft = true;
        mWaitNextPage = false;
        mPageCount++;
        mCurrentPage = mPageCount;
        Page page;
        mPages[mCurrentPage] = page;
        if(mCurrentPage > 1) FlipRight();
    }
}

void Book::PreviousPage()
{
    SDL_Log("Page: %d %d/%d\n", IsAnimating(), mCurrentPage, mPageCount);
    if(!IsAnimating() && mCurrentPage > 1) {
        mCurrentPage--;
        mLeftAnimatedText->SetText(mPages[mCurrentPage].leftPageText, true);
        mRightAnimatedText->SetText(mPages[mCurrentPage].rightPageText, true);
        FlipLeft();
    }
}

void Book::NextPage()
{
    SDL_Log("Page: %d %d/%d\n",IsAnimating(), mCurrentPage, mPageCount);
    if(!IsAnimating() && mCurrentPage < mPageCount) {
        mCurrentPage++;
        mLeftAnimatedText->SetText(mPages[mCurrentPage].leftPageText, true);
        mRightAnimatedText->SetText(mPages[mCurrentPage].rightPageText, true);
        FlipRight();
    }
}

void Book::FlipLeft()
{
    mFlipLeft->Play();
    mBookState = BookState::FLIPPING_LEFT;
}

void Book::FlipRight()
{
    mFlipRight->Play();
    mBookState = BookState::FLIPPING_RIGHT;
}

void Book::TheEnd()
{
    mEnd = true;
}

void Book::WaitNextPage()
{
    mWaitNextPage = true;
}

bool Book::IsWaitNextPage()
{
    return mWaitNextPage;
}

bool Book::IsAnimating()
{
    return !mLeftAnimatedText->End() || !mRightAnimatedText->End();
}

bool Book::IsOpen()
{
    return mBookState == BookState::OPENED;
}

bool Book::IsInLastPage()
{
    return mCurrentPage == mPageCount;
}

void Book::Update(float delta)
{
    switch(mBookState)
    {
        case BookState::CLOSED:
            // mBookClosed->Update(delta);
            break;
        case BookState::OPENED:
            if(mBookTab == BookTab::STORY) {
                mLeftAnimatedText->Update(delta);
                if(mLeftAnimatedText->End()) mRightAnimatedText->Update(delta);
            }
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
                mBookState = BookState::OPENED;
                mBookTab = mNextTab;
            }
            break;
        case BookState::FLIPPING_RIGHT:
            mFlipRight->Update(delta);
            if(mFlipRight->End()) {
                mBookState = BookState::OPENED;
                mBookTab = mNextTab;
            }
            break;
    }
}

void Book::Input(SDL_Event event)
{
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
            // case SDLK_1:
            //     OpenTab(BookTab::STORY);
            //     break;
            // case SDLK_2:
            //     OpenTab(BookTab::PROFILE);
            //     break;
            // case SDLK_3:
            //     OpenTab(BookTab::STATUS);
            //     break;
            // case SDLK_4:
            //     OpenTab(BookTab::INVENTORY);
            //     break;
            // case SDLK_5:
            //     OpenTab(BookTab::QUESTS);
            //     break;
            // case SDLK_6:
            //     OpenTab(BookTab::SAVES);
            //     break;
            // case SDLK_7:
            //     OpenTab(BookTab::SETTINGS);
            //     break;
            case SDLK_SPACE:
                if(!mLeftAnimatedText->End()) mLeftAnimatedText->SkipAnimation();
                if(!mRightAnimatedText->End()) mRightAnimatedText->SkipAnimation();
                break;
            case SDLK_RETURN:
                 if(mBookState == BookState::OPENED && mBookTab == BookTab::STORY) {
                    if(mEnd) {
                        mBookClose->Play();
                        mBookState = BookState::CLOSING;
                    }
                    else if(mWaitNextPage) {
                        NewPage();
                    }
                }
                break;
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
                if(mBookState == BookState::OPENED && mBookTab == BookTab::STORY)
                {
                    PreviousPage();
                    // int prevTab = mBookTab;
                    // OpenTab(static_cast<BookTab>(prevTab - 1));
                }
                break;
            case SDLK_d:
                if(mBookState == BookState::OPENED && mBookTab == BookTab::STORY)
                {
                    NextPage();
                    // int nextTab = mBookTab;
                    // OpenTab(static_cast<BookTab>(nextTab + 1));
                }
                break;
        }
    }
}

void Book::Render()
{
    if(mBookState != BookState::CLOSED && mBookState != BookState::OPENING && mBookState != BookState::CLOSING)
    {
        mBookTabTextures[mBookTab]->Render();
        if(mBookTab == BookTab::STORY) {
            // if(mPages[mCurrentPage].leftPageText.length()) RenderManager::Instance()->RenderWrappedText(mPages[mCurrentPage].leftPageText, mLeftPage.x, mLeftPage.y, mLeftPage.w, mLeftPage.h);
            // if(mPages[mCurrentPage].rightPageText.length()) RenderManager::Instance()->RenderWrappedText(mPages[mCurrentPage].rightPageText, mRightPage.x, mRightPage.y, mRightPage.w, mRightPage.h);
            mLeftAnimatedText->Render();
            mRightAnimatedText->Render();
        }
    }
    switch(mBookState)
    {
        case BookState::CLOSED:
            mBookClosed->Render();
            break;
        case BookState::OPENED:
            // mBookTabTextures[mBookTab]->Render();
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

size_t Book::Split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}
