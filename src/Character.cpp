#include "Character.h"

Character::Character()
{
    mInventory = new Inventory(this, 45, 300);
    mEquipment = new Equipment(this, 45, 220);
    mStats = new Stats(this);

    mIconsBackground = new Texture("assets/Inventory.png", {2, SCREEN_HEIGHT-38, 138, 36}, {0, 0, 1, 1});
    mStatsIcon = new Texture("assets/PNG/visored-helm.png", 4, SCREEN_HEIGHT-36);
    mInventoryIcon = new Texture("assets/PNG/knapsack.png", 34, SCREEN_HEIGHT-36);
    mJournalIcon = new Texture("assets/PNG/scroll-unfurled.png", 68, SCREEN_HEIGHT-36);
    
    mActiveTab = StatsTab;
}

Character::~Character()
{
    delete mStatsIcon;
    mStatsIcon = nullptr;

    delete mInventoryIcon;
    mInventoryIcon = nullptr;

    delete mJournalIcon;
    mJournalIcon = nullptr;

    delete mIconsBackground;
    mIconsBackground = nullptr;

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

void Character::Update()
{
    switch (mActiveTab)
    {
    case Character::StatsTab:
        mStats->Update();
        break;
    case Character::InventoryTab:
        // mEquipment->Update();
        // mInventory->Update();
        break;
    case Character::JournalTab:
        break;
    }
}

void Character::Input(SDL_Event event)
{
    int x = event.motion.x;
    int y = event.motion.y;

    SDL_Rect rect = mStatsIcon->Pos();
    if(event.type == SDL_MOUSEBUTTONUP && x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h)
    {
        mActiveTab = Character::StatsTab;
    }
    rect = mInventoryIcon->Pos();
    if(event.type == SDL_MOUSEBUTTONUP && x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h)
    {
        mActiveTab = Character::InventoryTab;
    }
    rect = mJournalIcon->Pos();
    if(event.type == SDL_MOUSEBUTTONUP && x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h)
    {
        mActiveTab = Character::JournalTab;
    }

    switch (mActiveTab)
    {
    case Character::StatsTab:
        mStats->Input(event);
        break;
    case Character::InventoryTab:
        mEquipment->Input(event);
        mInventory->Input(event);
        break;
    case Character::JournalTab:
        break;
    }
}

void Character::Render()
{
    mIconsBackground->Render();
    mStatsIcon->Render();
    mInventoryIcon->Render();
    mJournalIcon->Render();
    switch (mActiveTab)
    {
    case Character::StatsTab:
        mStats->Render();
        break;
    case Character::InventoryTab:
        mEquipment->Render();
        mInventory->Render();
        mEquipment->RenderItems();
        mInventory->RenderItems();
        break;
    case Character::JournalTab:
        break;
    }
}

void Character::SetActive(Character::CharacterTabs tab)
{
    mActiveTab = tab;
}

Character::CharacterTabs Character::Active()
{
    return mActiveTab;
}
