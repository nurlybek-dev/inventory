#ifndef _STATS_H_
#define _STATS_H_

#include <map>
#include <SDL2/SDL.h>

enum StatType {
    HEALTH,
    DAMAGE,
    ARMOR,
};

class Character;
class Stats {
    public:
        Stats(Character* character);
        ~Stats();

        int GetStat(StatType stat);
        void AddStat(StatType stat, int value);

        Character* GetCharacter();
    
    private:
        Character* mCharacter;
        std::map<StatType, int> mStats;
};

#endif