#ifndef _PANEL_H_
#define _PANEL_H_

#include "Texture.h"

class Panel
{
    public:
        Panel(int w, int h);
        ~Panel();

        void SetPos(int x, int y);
        SDL_Rect Pos();

        void SetWidth(int w);
        void SetHeight(int h);

        int GetWeight();
        int GetHeight();

        void Render();

    private:
        SDL_Rect mPos;

        Texture* mMiddle;
        Texture* mTop;
        Texture* mLeft;
        Texture* mRight;
        Texture* mBottom;

};

#endif