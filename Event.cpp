#include "Header-files/Event.h"

Event::Event()
{
    this->nrOfEvents = 2;
}

Event::~Event()
{

}

void Event::generateEvent(Character &character, dArr<Enemy>& enemies)
{
    int i = rand() % this->nrOfEvents;

    switch (i)
    {
        case 0:
            cout << "Enemy!\n";
            enemyEncounter(character, enemies);
            break;
        case 1:
            cout << "Puzzle!\n";
            puzzleEncounter(character);
            break;
        case 2:
            break;
        default:
            break;
    }
}

//different events
void Event::enemyEncounter(Character &character, dArr<Enemy>& enemies)
{
    bool playerTurn = false;
    int choice = 0;

    int coinToss = rand() % 1 + 1;

    if (coinToss == 1)
        playerTurn = true;
    else
        playerTurn = false;

    bool escape = false;
    bool playerDefeated = false;
    bool enemiesDefeated = false;

    int nrOfEnemies = rand() % 5;

    for (size_t i = 0; i < nrOfEnemies; i++)
    {
        enemies.push(Enemy(character.getLevel()));
    }

    while(!escape && !playerDefeated && !enemiesDefeated)
    {
        if (playerTurn && !playerDefeated)
        {
            //system("CLS");
            cout << "-=Battle menu=-" << "\n\n";
            cout << "0: Escape" << "\n";
            cout << "1: Attack" << "\n";
            cout << "2: Defend" << "\n";
            cout << "3: Use item" << "\n";
            cout << "\n";
            cout << "Choose your action: ";
            cin >> choice;

            while (cin.fail() || choice > 3 || choice < 0)
            {
                //system("CLS");
                cout << "Faulty input!" << "\n";
                cin.clear();
                cin.ignore(100, '\n');

                cout << "-=Battle menu=-" << "\n\n";
                cout << "0: Escape" << "\n";
                cout << "1: Attack" << "\n";
                cout << "2: Defend" << "\n";
                cout << "3: Use item" << "\n";
                cout << "\n";
                cout << "Choose your action: ";
                cin >> choice;
            }

            cin.ignore(100, '\n');
            cout << "\n";

            switch (choice)
            {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                default:
                    break;
            }

            playerTurn = false;
        }
        else if (!playerTurn && !escape && !enemiesDefeated)
        {
            for (size_t i = 0; i < enemies.size(); i++)
            {

            }

            playerTurn = true;
        }

        if (!character.isAlive())
        {
            playerDefeated = true;
        }

        else if (enemies.size() <= 0)
        {
            enemiesDefeated = true;
        }
    }
}

void Event::puzzleEncounter(Character &character)
{
    bool completed = false;
    int userAns = 0;
    int chances = 3;

    Puzzle puzzle("Puzzles/1.txt");

    while(!completed && chances > 0)
    {
        cout << "Chances left: " << chances << "\n\n";
        cout << puzzle.getAsString() << "\n";

        cout << "\nYour answer: ";
        cin >> userAns;

        while (cin.fail())
        {
            cout << "Faulty input!" << "\n";
            cin.clear();
            cin.ignore(100, '\n');

            cout << "\nYour answer: ";
            cin >> userAns;
        }

        cin.ignore(100, '\n');
        cout << "\n";

        if (puzzle.getCorrectAns() == userAns)
        {
            completed = true;
            int gainExp = chances * (rand() % 5 + 5) + 20;
            character.gainExp(gainExp);
            cout << "You gained " << gainExp << " EXP!" << "\n\n";
        }
        chances--;
    }
    if (completed)
    {
        cout << "CONGRATZ! YOU SUCCEEDED! \n\n";
    } else {
        cout << "YOU FAILED BRAH! \n\n";
    }
}