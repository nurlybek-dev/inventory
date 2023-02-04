#include "Dialogue.h"
#include "RenderManager.h"

Dialogue::Dialogue(const std::string& id, const std::string &text)
{
    mID = id;
    mText = text;
}

Dialogue::Dialogue(const std::string& id, const std::string &text, const std::vector<Choice> &choices) : Dialogue(id, text)
{
    mChoices.clear();
    mChoices = choices;
}

Dialogue::~Dialogue()
{
}

void Dialogue::SetText(const std::string &text)
{
    mText = text;
}

void Dialogue::SetChoices(const std::vector<Choice> &choices)
{
    mChoices.clear();
    mChoices = choices;
}

void Dialogue::AddChoise(const Choice &choice)
{
    mChoices.push_back(choice);
}

std::vector<Choice> Dialogue::GetChoices() const
{
    return mChoices;
}
