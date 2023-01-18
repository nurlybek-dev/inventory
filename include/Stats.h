#ifndef _STATS_H_
#define _STATS_H_

#include <map>
#include <SDL2/SDL.h>
#include "Button.h"

class Character;
class Stats {
    public:
        enum StatType {
            STRENGTH,
            AGILITY,
            INTELLIGENT,
            HEALTH,
            DAMAGE,
            ARMOR,
        };
    public:
        Stats(Character* character);
        ~Stats();

        int GetStat(Stats::StatType stat);
        void AddStat(Stats::StatType stat, int value);

        Character* GetCharacter();

        void Update();
        void Render();
        void Input(SDL_Event event);
    
    private:
        Character* mCharacter;
        std::map<StatType, int> mStats;
        int mRemainingPoints;

        Button* mButtonAddHealth;
        Button* mButtonAddStr;
        Button* mButtonAddAgi;
        Button* mButtonAddInt;
};

#endif