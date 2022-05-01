#include "Header-files/Event.h"

Event::Event()
{
    this->nrOfEvents = 2;
}

Event::~Event()
{

}

void Event::generateEvent(Character &character)
{
    int i = rand() % this->nrOfEvents;

    switch (i)
    {
        case 0:
            cout << "Enemy!\n";
            enemyEncounter(character);
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
void Event::enemyEncounter(Character &character)
{
//while()
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