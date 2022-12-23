#include "Stats.h"
#include "Character.h"

Stats::Stats(Character* character)
{
    mCharacter = character;
    mStats[HEALTH] = 0;
    mStats[DAMAGE] = 0;
    mStats[ARMOR] = 0;
}

Stats::~Stats()
{

}

int Stats::GetStat(StatType stat)
{
    return mStats[stat];
}

void Stats::AddStat(StatType stat, int value)
{
    mStats[stat] += value;

    SDL_Log("--------\n");
    SDL_Log("HEALTH: %d\n", mStats[HEALTH]);
    SDL_Log("DAMAGE: %d\n", mStats[DAMAGE]);
    SDL_Log("ARMOR: %d\n", mStats[ARMOR]);
}

Character* Stats::GetCharacter()
{
    return mCharacter;
}
