#include "DialogueManager.h"

DialogueManager::DialogueManager()
{
    Dialogue prolog1;
    prolog1.id = "prolog1";
    prolog1.text = "Рыцари всегда занимали особое место в сердцах людей. Они были героями и защитниками народа, ведь они не боялись подвергать свои жизни опасности, чтобы спасти невинных и защитить слабых. Они представляли собой символ отваги и могущества, сражались с самыми страшными существами, и отправлялись в самые опасные путешествия.";
    prolog1.type = DialogueType::STORY;
    prolog1.nextID = "prolog2";

    Dialogue prolog2;
    prolog2.id = "prolog2";
    prolog2.text = "Рыцари не боялись вступать в битву с драконами, которые грозили их деревням и городам. И они безукоризненно следовали своим принципам, чтобы спасти принцесс, которых пытались украсть злые властители.";
    prolog2.type = DialogueType::STORY;
    prolog2.nextID = "prolog3";

    Dialogue prolog3;
    prolog3.id = "prolog3";
    prolog3.text = "Добро пожаловать в мир Рыцарей! Мечтаешь ли ты стать рыцарем и защищать свою страну от зла или же ищешь славы и богатства, все это достанется тебе, если ты станешь рыцарем! Отправляйся в столицу, чтобы стать оруженосцем и начать обучение рыцарству. Но твой путь не будет легким, и ты встретишь разные препятствия, которые предстоит преодолеть. Готов ли ты к этому путешествию и стать настоящим рыцарем?";
    prolog3.type = DialogueType::CHOICE;
    prolog3.choices = {Choice("В путь.", "chapter1_1"), Choice("Пойти работать на поле.", "-1")};

    Dialogue chapter1_1;
    chapter1_1.id = "chapter1_1";
    chapter1_1.text = "Деревня в который в ты живешь, небольшая и уютная. Распложенная в уединенном месте, вдали от столицы. Дома в деревне выстроены из дерева и окружены большими садами, где растут фрукты и овощи. Жизнь в деревне тихая и спокойная. На главной площади находится фонтан, вокруг которого собираются жители деревни в свободное время.";
    chapter1_1.type = DialogueType::STORY;
    chapter1_1.nextID = "chapter1_2";

    Dialogue chapter1_2;
    chapter1_2.id = "chapter1_2";
    chapter1_2.text = "Жители дружелюбные и заботливые, они всегда готовы прийти на помощь в несложных делах. Услышав что ты уходишь из деревни, люди собрались на площади что бы проводить тебя.";
    chapter1_2.type = DialogueType::STORY;
    chapter1_2.nextID = "chapter1_3";

    Dialogue chapter1_3;
    chapter1_3.id = "chapter1_3";
    chapter1_3.text = "Староста выходит вперед что бы отдать тебе провизию которую они собрали и спрашивает тебя";
    chapter1_3.type = DialogueType::STORY;
    chapter1_3.nextID = "chapter1_4";

    Dialogue chapter1_4;
    chapter1_4.id = "chapter1_4";
    chapter1_4.text = "Ты уже выбрал каким путем пойдешь?";
    chapter1_4.type = DialogueType::CHOICE;
    chapter1_4.choices = {
        Choice("Через поле, хочу добраться по скорее в столицу", "-1"), 
        Choice("Выйду на тракт, и попробую добраться вместе с проходящими каретами.", "-1")
    };


    Dialogue lastDialogue;
    lastDialogue.id = "-1";
    lastDialogue.type = DialogueType::STORY;

    mDialogues[prolog1.id] = prolog1;
    mDialogues[prolog2.id] = prolog2;
    mDialogues[prolog3.id] = prolog3;

    mDialogues[chapter1_1.id] = chapter1_1;
    mDialogues[chapter1_2.id] = chapter1_2;
    mDialogues[chapter1_3.id] = chapter1_3;
    mDialogues[chapter1_4.id] = chapter1_4;

    mDialogues[lastDialogue.id] = lastDialogue;

    mCurrentDialogue = "prolog1";
    mLastDialogue = "-1";
}

DialogueManager::~DialogueManager()
{
    mDialogues.clear();
}

DialogueType DialogueManager::GetType()
{
    return mDialogues[mCurrentDialogue].type;
}

std::string DialogueManager::NextID()
{
    return mDialogues[mCurrentDialogue].nextID;
}

bool DialogueManager::IsEnd()
{
    return mCurrentDialogue == mLastDialogue;
}

std::string DialogueManager::GetText()
{
    return mDialogues[mCurrentDialogue].text;
}

std::vector<Choice> DialogueManager::GetChoices()
{
    return mDialogues[mCurrentDialogue].choices;
}

void DialogueManager::SelectChoice(int index)
{
    mCurrentDialogue = mDialogues[mCurrentDialogue].choices[index].nextID;
}

void DialogueManager::Next()
{
    mCurrentDialogue = mDialogues[mCurrentDialogue].nextID;
}
