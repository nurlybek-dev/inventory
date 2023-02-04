#ifndef _DIALOGUE_MANAGER_H_
#define _DIALOGUE_MANAGER_H_

#include <map>
#include <vector>
#include <string>

struct Choice
{
    Choice(std::string text, std::string nextID) : text(text), nextID(nextID) {}
    std::string text;
    std::string nextID;
};

struct Dialogue
{
    std::string id;
    std::string text;
    std::vector<Choice> choices;
};

class DialogueManager {
    public:
        DialogueManager();
        ~DialogueManager();

        std::string GetText();
        std::vector<Choice> GetChoices();

        void SelectChoice(int index);

        bool IsEnd();

    private:
        std::map<std::string, Dialogue> mDialogues;
        std::string mCurrentDialogue;
        std::string mLastDialogue;
};

#endif