#include <iostream>
#include <fstream> 
#include <chrono>
#include <thread>
#include <cstdlib>
#include <string>
#include <ctime>

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

struct Cloth : Treasure
{
    Cloth(ValueQuality quality) : Treasure(quality) {};
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

int GetRandom(int min, int max)
{
    return min + std::rand() % (max - min + 1);
}

int AttackEnemy(Player* player, Enemy* enemy)
{
    int damage = player->GetCharacter()->CalculateDamage();

    enemy->TakeDamage(damage);
    printSlowly("Вы нанесли ", false);
    printSlowly(to_string(damage), 4, false, Yellow);
    printSlowly(" урона.\n ", false);

    enemy->GetInfo();

    Pause(false);

    return damage;
}

int EnemyAttack(Player* player, Enemy* enemy)
{
    int damage = enemy->GetDamage();

    printSlowly("Враг атакует! Оставшееся здоровье: ", false);
    player->GetCharacter()->TakeDamage(damage);
    printSlowly(to_string(player->GetCharacter()->GetHealth()),2 ,false, Red);

    Pause(false);

    return damage;
}

void Fight(bool attackFirst, Player* player, Enemy* enemy)
{
    if (attackFirst)
    {
        printSlowly("\nВы атакуете первым. ", false);

        while (enemy->GetHealth() > 0 && player->GetCharacter()->GetHealth() > 0)
        {
            AttackEnemy(player, enemy);
            if (enemy->GetHealth() <= 0)
                continue;
            EnemyAttack(player, enemy);
        }
        if (enemy->GetHealth() <= 0)
        {
            printSlowly("Вы одолели врага!\n\n", false);
            return;
        }
        else
        {
            ClearScreen();
            printSlowly("ВЫ ПОГИБЛИ!",3, false, Red);
            exit(0);
        }
    }
    else
    {
        printSlowly(enemy->GetName(), false);
        printSlowly(" атакует первым.", true);

        while (enemy->GetHealth() > 0 && player->GetCharacter()->GetHealth() > 0)
        {
            EnemyAttack(player, enemy);
            if (player->GetCharacter()->GetHealth() <= 0)
                continue;
            AttackEnemy(player, enemy);
        }
        if (enemy->GetHealth() <= 0)
        {
            printSlowly("Вы одолели врага!\n\n", false);
            return;
        }
        else
        {
            ClearScreen();
            printSlowly("ВЫ ПОГИБЛИ!", 3, false, Red);
            exit(0);
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(std::time(0));

    Player* player = new Player();

    ShowName("Настройка");
    printSlowly("Выберите скорость текста:\n\t1 - Медленная\n\t2 - Оптимальная\n\t3 - Быстрая\n\t4 - Моментальная\n", false);

    switch (TestChoise(4, "Такой настройки нет!"))
    {
    case 1:
        ChangeDefaultSpeed(30);
        break;
    case 2:
        ChangeDefaultSpeed(60);
        break;
    case 3:
        ChangeDefaultSpeed(90);
        break;
    case 4:
        ChangeDefaultSpeed(0);
        break;
    }

    ClearScreen();

    printSlowly("Вы очнулись на опушке леса.\n", false);
    printSlowly("Придя в себя вы проверяете карманы и находите плесневый кусок хлеба и оружие.\n", false);
    printSlowly("Поднявшись и немного пройдя сквозь лесные заросли вы набредаете на просёлочную дорогу.\n", false);
    printSlowly("Вы следуете этому пути в надежде наткнуться на поселение.\n", false);
    printSlowly("Спустя некоторое время скитаний в вас разыгрался аппетит.\n", false);
    printSlowly("Вы собираетесь употребить свой единственный паёк, но из куста выползает исхудалая шавка учуявшая затхлый запах хлеба.\n", false);
    printSlowly("Вы смотрите в жалобные глазёнки пса, он смотрит в ответ.\n", false);
    printSlowly("Вы смотрите на хлеб, пёс делает тоже самое.\n\n", false);
    printSlowly("Отдать последее что у вас есть псу?\n\t", false);

    string dogName;

    printSlowly("1 - Пускай кушает.\n\t2 - Я сам жрать хочу!\n", false);

    switch (TestChoise(2, "Так не получится."))
    {
    case 1:
        ClearScreen();
        printSlowly("Вы бросаете горбушку псу, он жадно её пожирает.\n\n", false);
        ShowName("Псина");
        printSlowly("От души бро!\n\n", false);
        printSlowly("Пёс становится вашим компаньоном.\n\n", 20, false);
        printSlowly("Вы продолжаете путешествие с новым другом! Как вы его назовёте?\n\n", true);

        cin >> dogName;

        break;
    case 2:
        ClearScreen();
        printSlowly("Вы плюёте в сторону и прячете хлеб в карман. Пёс смотрит в вашу сторону\n\n", false);
        ShowName("Псина");
        printSlowly("Подонок.\n\n", false);
        printSlowly("Пёс умер.\n", 3, true);

        dogName = "";

        Pause(true);
        break;
    }

    ClearScreen();

    printSlowly("Вы забредаете в самую чащу леса.\n\n", false);

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
    if (dogName.empty())
        printSlowly("Я Марк, воин! Ты чего забыл в этом лесу?", true);
    else
        printSlowly("Я Марк, воин! Что ты со своей псиной забыл в этом лесу?", true);

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

    TestChoise(1, "Отказаться не получится, вам его жалко.");

    ClearScreen();

    ShowName("Марк");
    printSlowly("Спасибо, друг! Так и куда мы путь держим?\n", false);

    Pause(false);

    ShowName(playerCharacter->GetName());
    printSlowly("Я направлялся в ", false);
    printSlowly("Лес Фей.", 20, false, Purple);
    printSlowly("\nГоворят там живёт фея Мантра, самая долгоживущая из своего рода. ", false);
    printSlowly("Она явно что-то знает.", true);

    ClearScreen();

    printSlowly("Вы отправляетесь в ", 10, false);
    printSlowly("Лес Фей", 3, false, Purple);
    printSlowly("...", 1, true);

    ClearScreen();

    printSlowly("По дороге вы нашли старое разрушенное здание, рядом стоит сундук. ", false);
    printSlowly("Вы хотите открыть сундук?\n\t 1 - Взглянуть.\n\t 2 - Не сотоит.\n", false);


    if (TestChoise(2) == 1)
    {
        ClearScreen();

        printSlowly("Вам повезло! Помимо ненужного хлама вы нашли ", false);
        printSlowly("Кристал Жизни", 5, false, Red);
        printSlowly(". Максимальный уровень здоровья увеличен на (5).\n", true);

        playerCharacter->ChangeMaxHealth(5);

        playerCharacter->GetInfo();
        cout << endl;
        Pause(true);

        if (!dogName.empty())
        {
            ShowName(dogName);
            printSlowly("Вот это халява!", true);
        }
    }
    else
    {
        ClearScreen();

        printSlowly("Вы решили что трогать чужое - плохо.", true);
        Pause(false);
    }

    ClearScreen();

    Enemy* enemy = new Enemy("Волк обыкновенный", 30, 5);

    printSlowly("Вы продолжаете свой путь...\n", false);
    printSlowly("Вы встретили лесную тварь, она настроена враждебно.\n", true);

    enemy->GetInfo();

    printSlowly("Вы хотите с ней сразиться?\n\t", false);
    printSlowly("1 - Погнали!\n\t2 - Сбежать (Шанс на успех 50%)\n", false);

    if (TestChoise(2) == 1)
    {
        ClearScreen();
        Fight(true, player, enemy);
    }
    else
    {
        if (GetRandom(1, 2) == 1)
        {
            ClearScreen();
            printSlowly("Избежать драки не получилось ", false);
            Fight(false, player, enemy);
        }
        else
        {
            ClearScreen();
            printSlowly("\nВы смогли уйти от конфликта!\n", true);
        }
    }

    if (!dogName.empty())
    {
        ShowName(dogName);
        printSlowly("Ай харош!\n\n", false);
    }

    Pause(true);

    ClearScreen();

    printSlowly("После драки вы продолжаете путешесвие и забредаете на поляну.\n", false);
    printSlowly("Посреди неё стоит сундук.\n", false);
    printSlowly("Хотите его открыть?\n\t", false);
    printSlowly("1 - Конечно!\n\t2 - Не стоит\n", false);
    
    enemy = new Enemy("Мимик", 20, 3);

    switch (TestChoise(2, "Не-а"))
    {
    case 1:
        ClearScreen();
        printSlowly("Это же был очевидный мимик...\n\n", false);
        Fight(false, player, enemy);
        if (!dogName.empty())
        {
            ShowName(dogName);
            printSlowly("Чувак, это жесть!\n", true);
        }
        break;
    case 2:
        ClearScreen();
        printSlowly("Вы проходите мимо, погодите, это был мимик, вам повезло...\n\n", false);
        if (!dogName.empty())
        {
            ShowName(dogName);
            printSlowly("Хрен тебе мимик!\n", true);
            Pause(false);
        }
        break;
    }

    ClearScreen();

    ShowName("Марк");
    printSlowly("Я ничего не пропустил? У меня есть кое-что для тебя.\n", true);
    printSlowly("Марк подарил вам ", false);
    printSlowly("Зелье Исцеления\n\n", 10, false, Green);
    printSlowly("Вы были исцелены по максимуму!\n\n", false);

    playerCharacter->AddHealth(50);
    playerCharacter->GetInfo();

    cout << endl;
    
    ShowName(playerCharacter->GetName());
    printSlowly("Спасибо! Как раз не хватало!", true);

    ClearScreen();

    printSlowly("2 часа спустя...", 20, true);

    ClearScreen();

    ShowName("Марк");
    printSlowly("Мужик, у меня спина отваливается!", true);

    ShowName(playerCharacter->GetName());
    printSlowly("Мы почти на месте.", true);

    ClearScreen();

    printSlowly("Перед вами простирается самый красивый магический лес который вы когда-либо видели.\n", false);
    printSlowly("Вас разделяет только мутная река.", true);

    ClearScreen();

    printSlowly("Что вы сделаете?\n\t1 - Переплыть.\n\t2 - Поискать другой путь\n", false);

    switch (TestChoise(2, "Так-так"))
    {
    case 1:
        ClearScreen();
        printSlowly("Вы переплыли реку. Но вас покусали гигантские судаки...\n\n", false);
        playerCharacter->TakeDamage(10);
        printSlowly("Вы потеряли здоровье:", false);
        printSlowly("10\n\n", 20, false, Red);
        playerCharacter->GetInfo();

        cout << endl;

        break;
    case 2:
        ClearScreen();
        ShowName("Марк");
        printSlowly("Тут да моста рукой подать, вижу его отсюда.\n\n", false);
        printSlowly("Вы перешли реку по мосту.\n", false);
        break;
    }

    Pause(false);
    Pause(true);

    ClearScreen();

    printSlowly("Вы посетили новую локацию и стали сильнее!\n\n", false);
    printSlowly("Вы получили новый уровень!\n", false);

    playerCharacter->NextLevel();

    playerCharacter->GetInfo();
    cout << endl;

    Pause(true);

    ClearScreen();

    return 0;
}