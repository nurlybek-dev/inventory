#ifndef _BOOK_H_
#define _BOOK_H_

#include <map>
#include "Animation.h"
#include "AnimatedText.h"

struct Page {
    std::string leftPageText;
    std::string rightPageText;
};

class Book
{
    public:
        enum BookState {
            CLOSED,
            OPENED,
            OPENING,
            CLOSING,
            FLIPPING_LEFT,
            FLIPPING_RIGHT,
        };
        enum BookTab {
            STORY,
            PROFILE,
            STATUS,
            INVENTORY,
            QUESTS,
            SAVES,
            SETTINGS,
        };
    public:
        Book();
        ~Book();

        void OpenTab(BookTab tab);

        bool IsTextFit(const std::string& text);

        void AddText(std::string text);

        void NewPage();
        void PreviousPage();
        void NextPage();
        void FlipLeft();
        void FlipRight();
        void TheEnd();
        void WaitNextPage();

        bool IsWaitNextPage();
        bool IsAnimating();
        bool IsOpen();
        bool IsInLastPage();

        void Update(float delta);
        void Input(SDL_Event event);
        void Render();


        size_t Split(const std::string &text, std::vector<std::string> &strings, char ch);

    private:
        SDL_Rect mLeftPage;
        SDL_Rect mRightPage;
 
        int mCurrentPage;
        int mPageCount;

        std::map<int, Page> mPages;

        int mWordsPerPage;
        int mCharsPerPage;

        int mLeftPageWords;
        int mRightPageWords;

        bool mIsWritingToLeft;

        bool mWaitNextPage;
        bool mEnd;

        AnimatedText *mLeftAnimatedText;
        AnimatedText *mRightAnimatedText;

        BookState mBookState;
        BookTab mBookTab;
        BookTab mNextTab;
        
        Texture* mBookClosed;
        Texture* mBookOpened;

        SDL_Rect mNextPageRect;
        SDL_Rect mPreviousPageRect;
        Texture* mNextPageTexture;
        Texture* mPreviousPageTexture;

        std::map<BookTab, Texture*> mBookTabTextures;

        Animation* mBookOpen;
        Animation* mBookClose;
        Animation* mFlipLeft;
        Animation* mFlipRight;
};

#endif