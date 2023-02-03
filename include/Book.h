#ifndef _BOOK_H_
#define _BOOK_H_

#include <map>
#include "Animation.h"

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

        void Update(float delta);
        void Input(SDL_Event event);
        void Render();
    private:
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