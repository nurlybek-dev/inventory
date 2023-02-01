#include "Tooltip.h"

Tooltip* Tooltip::sInstance = nullptr;

Tooltip* Tooltip::Instance()
{
    if(sInstance == nullptr)
        sInstance = new Tooltip();

    return sInstance;
}

void Tooltip::Release()
{
    delete sInstance;
    sInstance = nullptr;
}

Tooltip::Tooltip()
{
    mTitle = "";
    mDescription = "";
    mEffects.clear();
    mShow = false;
    mBackground = new Texture("assets/Inventory.png", {0, 0, 0, 0}, {3, 3, 1, 1});
}

Tooltip::~Tooltip()
{
    delete mBackground;
    mBackground = nullptr;
}

bool Tooltip::Show()
{
    return mShow;
}

void Tooltip::Show(Item* item)
{
    mShow = true;
    mTitle = item->Name();
    mDescription = item->Description();
    mEffects.clear();
    for(auto &&e: item->GetEffects())
    {
        switch (e.first)
        {
        case Stats::HEALTH:
            mEffects.push_back("+" + std::to_string(e.second) + " health");
            break;
        case Stats::DAMAGE:
            mEffects.push_back("+" + std::to_string(e.second) + " damage");
            break;
        case Stats::ARMOR:
            mEffects.push_back("+" + std::to_string(e.second) + " armor");
            break;
        }
    }
}

void Tooltip::Show(MapNode* node)
{
    mShow= true;
    mEffects.clear();
    mTitle = node->Name();
    mDescription = node->Description();
}

void Tooltip::Hide()
{
    mShow = false;
}

void Tooltip::Render()
{
    if(mShow)
    {
        int fontSize = 16;
        int x, y;
        int w = 200;
        int h = fontSize + 4 + fontSize*2 + 4 + mEffects.size() * fontSize + 4;
        SDL_GetMouseState(&x, &y);
        x += 10;
        y += 10;
        mBackground->SetPos(x, y);
        mBackground->SetWidth(w);
        mBackground->SetHeight(h);
        mBackground->Render();

        RenderManager::Instance()->RenderText(mTitle, x, y, fontSize);

        for(int i=0; i < mEffects.size(); i++) {
            RenderManager::Instance()->RenderText(mEffects[i], x, y+((i+1)*fontSize)+4, fontSize);
        }

        RenderManager::Instance()->RenderWrappedText(mDescription, x, y+(int)((mEffects.size()+1) * fontSize)+4, w, fontSize);
    }
}