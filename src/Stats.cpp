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
}

Character* Stats::GetCharacter()
{
    return mCharacter;
}
