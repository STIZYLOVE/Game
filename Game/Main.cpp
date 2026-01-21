#include <iostream>
#include <fstream> 
#include <chrono>
#include <thread>
#include <cstdlib>

#include "windows.h"

#include "Ninja.h"
#include "Warrior.h"
#include "Assasin.h"
#include "NpcClass.h"
#include "playerClass.h"
#include "Enemy.h"
#include "ConsoleManager.h"

using namespace std;

enum ColorConsole {
    Black = 0,
    DarkBlue = 1,
    Green = 2,
    Blue = 3,
    Red = 4,
    Purple = 5,
    Yellow = 6,
    White = 7,
    Gray = 8
};

enum class ValueQuality
{
    МУСОР, ОБЫЧНОЕ, РЕДКОЕ, МИФИЧЕСКОЕ, ЛЕГЕНДАРНОЕ
};

struct Treasure
{
    Treasure() = default;
    string name{ "добыча" };
    ValueQuality quality = ValueQuality::МИФИЧЕСКОЕ;
    unsigned int price{ 0 };
    Treasure(ValueQuality quality)
    {
        switch (quality)
        {
        case ValueQuality::МУСОР:
            cout << "качество плохое\n";
            break;
        case ValueQuality::ОБЫЧНОЕ:
            cout << "качество средненькое\n";
            break;
        case ValueQuality::РЕДКОЕ:
            cout << "качество хорошее\n";
            break;
        case ValueQuality::МИФИЧЕСКОЕ:
            cout << "качество крутое\n";
            break;
        case ValueQuality::ЛЕГЕНДАРНОЕ:
            cout << "качество идеальное\n";
            break;
        default:
            break;
        }
    }
};

struct Сloth : Treasure
{
    Сloth(ValueQuality quality) : Treasure(quality) {};
    string valueSite[5]{ "Ботинки", "Поножи", "Нагрудник", "Шлем"};
    string site{ NULL };
    unsigned short armor{ 1 };
};

enum class CharacterType {
    UNKNOWN,
    WARRIOR,
    ASSASIN,
    NINJA
};

unsigned short TestChoise(unsigned short maxChoise, string text)
{
    unsigned short choise = 1;
    cin >> choise;
    while (choise > maxChoise || choise < 1)
    {
        cout << text << endl;
        cin >> choise;
    }
    return choise;
};

unsigned short TestChoise(unsigned short maxChoise)
{
    unsigned short choise = 1;
    cin >> choise;
    while (choise > maxChoise || choise < 1)
    {
        cout << "Такого выбора не существует!" << endl;
        cin >> choise;
    }
    return choise;
};

unique_ptr<Npc> CreateCharacter(CharacterType type)
{
    switch (type)
    {
    case CharacterType::UNKNOWN:
        return make_unique<Npc>();
        break;
    case CharacterType::WARRIOR:
        return make_unique<Warrior>();
        break;
    case CharacterType::ASSASIN:
        return make_unique<Assasin>();
        break;
    case CharacterType::NINJA:
        return make_unique<Ninja>();
        break;
    default:
        invalid_argument("Неизвестный тип персонажа");
        break;
    }
}

int main()
{
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Player* player = new Player();

    ShowName("Настройка");
    printSlowly("Выберите скорость текста:\n\t1 - Медленная\n\t2 - Оптимальная\n\t3 - Быстрая\n\t4 - Моментальная\n", false);

    switch (TestChoise(4, "Такой настройки нет!"))
    {
    case 1:
        ChangeDefaulSpeed(30);
        break;
    case 2:
        ChangeDefaulSpeed(60);
        break;
    case 3:
        ChangeDefaulSpeed(90);
        break;
    case 4:
        ChangeDefaulSpeed(0);
        break;
    }

    ClearScreen();

    ShowName("Незнакомец");
    printSlowly("Привет, путник\nПрисядь у костра и расскажи о себе\nТы кем будешь?\n\t", false);
    cout << "1 - Воин\n\t2 - Ассасин\n\t3 - Нинзя\n";

    unique_ptr<Npc> character;
    switch (TestChoise(3, "Чего-чего ты не ошибся ли?\nНе мог бы ты повторить"))
    {
    case 1:
        character = CreateCharacter(CharacterType::WARRIOR);
        break;
    case 2:
        character = CreateCharacter(CharacterType::ASSASIN);
        break;
    case 3:
        character = CreateCharacter(CharacterType::NINJA);
        break;
    }

    ClearScreen();

    player->Create(move(character));

    auto playerCharacter = player->GetCharacter();

    Pause(false);
    Pause(true);

    ClearScreen();

    ShowName("Незнакомец");
    printSlowly("Ну что, приятно познакомится ", false);
    printSlowly(playerCharacter->GetName() + "\n", 2, false);
    printSlowly("Я Марк, воин! Ты чего забыл в этом лесу?", true);

    ShowName(playerCharacter->GetName());
    printSlowly("Взаимно! Я блуждаю в этих лесах, чтобы найти полезные ", false);
    printSlowly("артефакты.", 4, true);

    ShowName("Марк");
    printSlowly("Ха-ха, да ладно, какие такие артефакты ты думаешь здесь затерялись?", true);

    ShowName(playerCharacter->GetName());
    printSlowly("Можешь смеяться сколько угодно, я намерен найти ", false);
    printSlowly("Четвёртый Дар.", 15, true, Yellow);

    ShowName("Марк");
    printSlowly("Ха-ха-ха, уже тринадцатое десятилетие, а ты всё веришь в эти сказки?", true);

    ShowName(playerCharacter->GetName());
    printSlowly("...", 1, true, Red);

    ShowName("Марк");
    printSlowly("Извини, я просто в который раз слышу об этом артефакте, но то всё были пустые слова.\n", false);
    printSlowly("Я вижу ты настроен крайне серьёзно, может я присоеденюсь к тебе? Меня всё равно выгнали из замка.\n", true);

    ClearScreen();

    printSlowly("Возьмёте ли вы Марка с собой?\n\t 1 - Хорошо, присоединяйся.\n\t 2 - Нет, извини.\n", false);

    TestChoise(1, "Отказаться не получится, он выглядит слишком растерянным.");

    ClearScreen();

    ShowName("Марк");
    printSlowly("Спасибо, друг! Так и куда мы путь держим?", true);

    Pause(false);

    ShowName(playerCharacter->GetName());
    printSlowly("Я направлялся в ", false);
    printSlowly("Лес Фей.", 20, false, Purple);
    printSlowly("\nГоворят там живёт фея Мантра, самая долгоживущая из своего рода. ", false);
    printSlowly("Она явно что-то знает.", true);

    ClearScreen();

    printSlowly("Вы отправляетесь в ", 10, false);
    printSlowly("Лес Фей",3,false, Purple);
    printSlowly("...", 1, true);

    printSlowly("По дороге вы нашли старое разрушенное здание, рядом стоит стундук. ", false);
    printSlowly("Вы хотите открыть сундук?\n\t 1 - Взглянуть.\n\t 2 - Не сотоит.\n", false);

    int choise;

    choise = TestChoise(2);

    ClearScreen();

    if (choise == 1)
    {
        printSlowly("Вам повезло! Помимо ненужного хлама вы нашли ", false);
        printSlowly("Кристал Жизни", 3, false, Red);
        printSlowly(". Максимальный уровень здоровья увеличен на (5).\n", true);

        playerCharacter->ChangeMaxHealth(5);

        playerCharacter->GetInfo();
        cout << endl;
        Pause(true);

        ShowName("Марк");
        printSlowly("Вот это халява!", true);
    }
    else if (choise == 2)
    {
        printSlowly("Вы решили что трогать чужое - плохо.", false);
    }

    return 0;
}