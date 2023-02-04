#ifndef _DIALOGUE_H_
#define _DIALOGUE_H_

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "AnimatedText.h"


struct Choice
{
    std::string text;
    std::string nextID;
};

class Dialogue 
{
    public:
        Dialogue(const std::string& id, const std::string &text);
        Dialogue(const std::string& id, const std::string &text, const std::vector<Choice>& choices);
        ~Dialogue();

        void SetText(const std::string& text);
        void SetChoices(const std::vector<Choice>& choices);
        void AddChoise(const Choice& choice);

        std::vector<Choice> GetChoices() const;

    private:
        std::string mID;
        std::string mText;
        std::vector<Choice> mChoices;
};

#endif