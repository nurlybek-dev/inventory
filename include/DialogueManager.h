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

enum DialogueType {
    STORY,
    CHOICE,
    COMBAT,
    ABILITY_CHECK,
};

struct Dialogue
{
    std::string id;
    std::string text;
    DialogueType type;
    std::string nextID;
    std::vector<Choice> choices;
};

class DialogueManager {
    public:
        DialogueManager();
        ~DialogueManager();

        DialogueType GetType();
        std::string NextID();

        std::string GetText();
        std::vector<Choice> GetChoices();

        void SelectChoice(int index);
        void Next();

        bool IsEnd();

    private:
        std::map<std::string, Dialogue> mDialogues;
        std::string mCurrentDialogue;
        std::string mLastDialogue;
};

#endif