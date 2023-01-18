#include "Item.h"
#include "Inventory.h"
#include "Equipment.h"

Item::Item(std::string name, std::string iconPath, ItemType itemType) 
{
    mName = name;
    mTexture = new Texture(iconPath);
    mType = itemType;
}

Item::~Item()
{
    delete mTexture;
    mTexture = nullptr;
}

void Item::SetPos(int x, int y)
{
    mTexture->SetPos(x, y);
}

SDL_Rect Item::Pos()
{
    return mTexture->Pos();
}

void Item::Render()
{
    mTexture->Render();
}

void Item::Input(SDL_Event event)
{
}

ItemType Item::Type()
{
    return mType;
}

std::string Item::Name()
{
    return mName;
}

std::string Item::Description()
{
    return mDescription;
}

void Item::Name(std::string name)
{
    mName = name;
}

void Item::Description(std::string description)
{
    mDescription = description;
}

void Item::AddEffect(Stats::StatType type, int value)
{
    mEffectors[type] = value;
}

std::map<Stats::StatType, int> Item::GetEffects()
{
    return mEffectors;
}

void Item::Effect(Stats* stat)
{
    for(auto &&e: mEffectors)
    {
        stat->AddStat(e.first, e.second);
    }
}

void Item::UnEffect(Stats* stat)
{
    for(auto &&e: mEffectors)
    {
        stat->AddStat(e.first, -e.second);
    }
}
