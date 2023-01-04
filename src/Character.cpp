#include "Character.h"

Character::Character(std::string iconPath, int x, int y)
{
    mInventory = new Inventory(this);
    mEquipment = new Equipment(this);
    mStats = new Stats(this);

    mIcon = new Texture(iconPath, x, y);
    mActive = false;
}

Character::~Character()
{
    delete mInventory;
    mInventory = nullptr;

    delete mEquipment;
    mEquipment = nullptr;

    delete mStats;
    mStats = nullptr;
}

Inventory* Character::GetInventory()
{
    return mInventory;
}

Equipment* Character::GetEquipment()
{
    return mEquipment;
}

Stats* Character::GetStats()
{
    return mStats;
}

void Character::Input(SDL_Event event)
{
    if(mActive)
    {
        mEquipment->Input(event);
        mInventory->Input(event);
    }
}

void Character::Render()
{
    if(mActive)
    {
        mEquipment->Render();
        mInventory->Render();
        mEquipment->RenderItems();
        mInventory->RenderItems();
    }
    mIcon->Render();
}

void Character::SetActive(bool value)
{
    mActive = value;
}

bool Character::Active()
{
    return mActive;
}

SDL_Rect Character::Pos()
{
    return mIcon->Pos();
}
