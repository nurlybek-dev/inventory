#include "Stats.h"
#include "Character.h"
#include "RenderManager.h"

Stats::Stats(Character* character)
{
    mCharacter = character;
    mStats[STRENGTH] = 0;
    mStats[AGILITY] = 0;
    mStats[INTELLIGENT] = 0;
    mStats[HEALTH] = 0;
    mStats[DAMAGE] = 0;
    mStats[ARMOR] = 0;

    mRemainingPoints = 1;

    mButtonAddHealth = new Button("+", 124, 200, 12, 12, 12);
    mButtonAddStr = new Button("+", 124, 212, 12, 12, 12);
    mButtonAddAgi = new Button("+", 124, 224, 12, 12, 12);
    mButtonAddInt = new Button("+", 124, 236, 12, 12, 12);
}

Stats::~Stats()
{
    delete mButtonAddHealth;
    mButtonAddHealth = nullptr;

    delete mButtonAddStr;
    mButtonAddStr = nullptr;

    delete mButtonAddAgi;
    mButtonAddAgi = nullptr;

    delete mButtonAddInt;
    mButtonAddInt = nullptr; 
}

int Stats::GetStat(Stats::StatType stat)
{
    return mStats[stat];
}

void Stats::AddStat(Stats::StatType stat, int value)
{
    mStats[stat] += value;
}

Character* Stats::GetCharacter()
{
    return mCharacter;
}

void Stats::Update(float delta)
{
    if(mRemainingPoints > 0) {
        mButtonAddHealth->Update(delta);
        mButtonAddStr->Update(delta);
        mButtonAddAgi->Update(delta);
        mButtonAddInt->Update(delta);
        if(mButtonAddHealth->IsPressed())
        {
            mStats[HEALTH]++;
            mRemainingPoints--;
            SDL_Log("Add Health\n");
        }
        else if(mButtonAddStr->IsPressed())
        {
            mStats[STRENGTH]++;
            mRemainingPoints--;
            SDL_Log("Add STR\n");
        }
        else if(mButtonAddAgi->IsPressed())
        {
            mStats[AGILITY]++;
            mRemainingPoints--;
            SDL_Log("Add AGI\n");
        }
        else if(mButtonAddInt->IsPressed())
        {
            mStats[INTELLIGENT]++;
            mRemainingPoints--;
            SDL_Log("Add INT\n");
        }
    }
}

void Stats::Render()
{
    RenderManager::Instance()->RenderText("Health", 4, 200, 12);
    RenderManager::Instance()->RenderText("Strength", 4, 212, 12);
    RenderManager::Instance()->RenderText("Agility", 4, 224, 12);
    RenderManager::Instance()->RenderText("Inteligent", 4, 236, 12);
    RenderManager::Instance()->RenderText("Damage", 4, 248, 12);
    RenderManager::Instance()->RenderText("Armor", 4, 262, 12);

    RenderManager::Instance()->RenderText(std::to_string(mStats[HEALTH]), 100, 200, 12);
    RenderManager::Instance()->RenderText(std::to_string(mStats[STRENGTH]), 100, 212, 12);
    RenderManager::Instance()->RenderText(std::to_string(mStats[AGILITY]), 100, 224, 12);
    RenderManager::Instance()->RenderText(std::to_string(mStats[INTELLIGENT]), 100, 236, 12);
    RenderManager::Instance()->RenderText(std::to_string(mStats[DAMAGE]), 100, 248, 12);
    RenderManager::Instance()->RenderText(std::to_string(mStats[ARMOR]), 100, 262, 12);

    if(mRemainingPoints > 0) {
        mButtonAddHealth->Render();
        mButtonAddStr->Render();
        mButtonAddAgi->Render();
        mButtonAddInt->Render();
    }
}

void Stats::Input(SDL_Event event)
{
    mButtonAddHealth->Input(event);
    mButtonAddStr->Input(event);
    mButtonAddAgi->Input(event);
    mButtonAddInt->Input(event);
}
