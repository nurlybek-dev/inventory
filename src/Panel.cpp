#include "Panel.h"

Panel::Panel(int w, int h)
{
    mPos = {0, 0, w, h};

    mMiddle = new Texture("assets/Inventory.png", {0,0,w,h}, {3,3, 1, 1});
    mTop = new Texture("assets/Inventory.png", {0,0,w,2}, {0,0, 1, 1});
    mLeft = new Texture("assets/Inventory.png", {0,0,2,h}, {0,0, 1, 1});
    mRight = new Texture("assets/Inventory.png", {w-2,0,2,h}, {0,0, 1, 1});
    mBottom = new Texture("assets/Inventory.png", {0,h-2,w,2}, {0,0, 1, 1});
}

Panel::~Panel()
{
    delete mBottom;
    mBottom = nullptr;

    delete mRight;
    mRight = nullptr;

    delete mLeft;
    mLeft = nullptr;

    delete mTop;
    mTop = nullptr;

    delete mMiddle;
    mMiddle = nullptr;
}

void Panel::SetPos(int x, int y)
{
    mPos.x = x;
    mPos.y = y;

    mMiddle->SetPos(x, y);
    mTop->SetPos(x, y);
    mLeft->SetPos(x, y);
    mRight->SetPos(Pos().w + x - mRight->GetWeight(), y);
    mBottom->SetPos(x, Pos().h + y - mBottom->GetHeight());

}

SDL_Rect Panel::Pos()
{
    return mPos;
}

void Panel::SetWidth(int w)
{
    mPos.w = w;

    mMiddle->SetWidth(w);
    mTop->SetWidth(w);
    mRight->SetPos(w - mRight->GetWeight(), 0);
    mBottom->SetWidth(w);
}

void Panel::SetHeight(int h)
{
    mPos.h = h;

    mMiddle->SetHeight(h);
    mLeft->SetHeight(h);
    mRight->SetHeight(h);
    mBottom->SetPos(0, h - mBottom->GetHeight());
}

int Panel::GetWeight()
{
    return mPos.w;
}

int Panel::GetHeight()
{
    return mPos.h;
}

void Panel::Render()
{
    mMiddle->Render();
    mTop->Render();
    mLeft->Render();
    mRight->Render();
    mBottom->Render();
}
