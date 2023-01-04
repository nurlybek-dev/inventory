#ifndef _TOOLTIP_H_
#define _TOOLTIP_H_

#include <string>
#include <vector>
#include "Item.h"

class Tooltip 
{
    public:
        static Tooltip* Instance();
        static void Release();

    public:
        Tooltip();
        ~Tooltip();

        bool Show();
        void Show(Item* item);
        void Hide();

        void Render();

    private:
        static Tooltip* sInstance;

        Texture* mBackground;

        std::string mTitle;
        std::string mDescription;
        std::vector<std::string> mEffects;

        bool mShow;

};

#endif