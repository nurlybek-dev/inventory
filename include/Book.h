#ifndef _BOOK_H_
#define _BOOK_H_

#include <map>
#include "Animation.h"
#include "AnimatedText.h"

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
            EMPTY,
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

        void AddText(std::string text);
        void AddChoice(std::string choice);

        void RenderText(std::string text);
        void NextPage();
        void TheEnd();

        bool WaitNextPage();
        bool IsAnimating();
        bool IsOpen();

        void Update(float delta);
        void Input(SDL_Event event);
        void Render();


        size_t Split(const std::string &text, std::vector<std::string> &strings, char ch);

    private:
        SDL_Rect mLeftPage;
        SDL_Rect mRightPage;

        int mWordsPerPage;
        int mCharsPerPage;

        int mLeftPageWords;
        int mRightPageWords;

        bool mWaitNextPage;
        bool mEnd;
        std::vector<std::string> mTextQueue;

        AnimatedText *mLeftAnimatedText;
        AnimatedText *mRightAnimatedText;

        BookState mBookState;
        BookTab mBookTab;
        BookTab mNextTab;
        
        Texture* mDeskTexture;
        Texture* mBookClosed;
        Texture* mBookOpened;

        std::map<BookTab, Texture*> mBookTabTextures;

        Animation* mBookOpen;
        Animation* mBookClose;
        Animation* mFlipLeft;
        Animation* mFlipRight;
};

#endif