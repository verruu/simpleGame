#include "Header-files/Event.h"

int Event::nrOfEvents = 3;

Event::Event()
{

}

Event::~Event()
{

}

void Event::generateEvent(Character &character, dArr<Enemy>& enemies)
{
    int i = rand() % Event::nrOfEvents;

    switch (i)
    {
        case 0:
            cout << "Enemy attack!\n";
            this->enemyEncounter(character, enemies);
            break;
        case 1:
            cout << "You've got a puzzle to solve!\n";
            this->puzzleEncounter(character);
            break;
        case 2:
            cout << "You've found a wandering merchant who wants to trade with you.\n";
            this->shopEncounter(character);
            break;
        default:
            break;
    }
}

//different events
void Event::enemyEncounter(Character &character, dArr<Enemy> &enemies)
{
    bool playerTurn = false;
    int choice = 0;

    //Coin toss for turn
    int coinToss = rand() % 1 + 1;

    if (coinToss == 1)
        playerTurn = true;
    else
        playerTurn = false;

    //End encounter conditions
    bool escape = false;
    bool playerDefeated = false;
    bool enemiesDefeated = false;

    //Enemies
    int nrOfEnemies = rand() % 5 + 1;

    for (size_t i = 0; i < nrOfEnemies; i++)
    {
        enemies.push(Enemy(character.getLevel() + rand() % 3));
    }

    for (size_t i = 0; i < enemies.size(); i++)
    {
        cout << i << ": " << "Level: " << enemies[i].getLevel() <<
             " HP: " << enemies[i].getHp() << "/" << enemies[i].getHpMax() <<
             " Defence: " << enemies[i].getDefence() << " Accuracy: " <<
             enemies[i].getAccuracy() <<
             " Damage: " << enemies[i].getDamageMin() << " - " << enemies[i].getDamageMax() << "\n";
    }

    //Battle variables and modifiers
    int damage = 0;
    int gainExp = 0;
    int gainGold = 0;
    int playerTotal = 0;
    int enemyTotal = 0;
    int combatTotal = 0;
    int combatRollPlayer = 0;
    int combatRollEnemy = 0;

    while(!escape && !playerDefeated && !enemiesDefeated)
    {
        if (playerTurn && !playerDefeated)
        {
            cout << "-=PLAYER TURN!=-" << "\n";
            cout << "Continue.." << "\n\n";
            cin.get();

            cout << "-=Battle menu=-" << "\n\n";
            cout << "Your Hp: " <<
            character.getHp() << "/" << character.getHpMax() << ". \n\n";
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
                case 0: //ESCAPE
                for (size_t i = 0; i < enemies.size(); i++)
                {
                    enemies.remove(i);
                }
                cout << "You have escaped the battle successfully!" << "\n";
                escape = true;
                    break;
                case 1: //ATTACK

                //Enemy selection
                    cout << "Select enemy: " << "\n\n";

                    for (size_t i = 0; i < enemies.size(); i++)
                    {
                        cout << i << ": " << "Level: " << enemies[i].getLevel() <<
                        " HP: " << enemies[i].getHp() << "/" << enemies[i].getHpMax() <<
                        " Defence: " << enemies[i].getDefence() << " Accuracy: " <<
                        enemies[i].getAccuracy() <<
                        " Damage: " << enemies[i].getDamageMin() << " - " << enemies[i].getDamageMax() << "\n";
                    }

                    cout << "\n";
                    cout << "Choice: ";
                    cin >> choice;

                    while (cin.fail() || choice >= enemies.size() || choice < 0)
                    {
                        //system("CLS");
                        cout << "Faulty input!" << "\n";
                        cin.clear();
                        cin.ignore(100, '\n');

                        cout << "Select enemy: " << "\n\n";

                        cout << "Choice: ";
                        cin >> choice;
                    }

                    cin.ignore(100, '\n');
                    cout << "\n";

                //Attack roll
                combatRollPlayer = rand() % 100 + 1;

                combatTotal = enemies[choice].getDefence() + character.getAccuracy();
                enemyTotal = enemies[choice].getDefence() / (double)combatTotal * 100;
                playerTotal = character.getAccuracy() / (double)combatTotal * 100;
                combatRollPlayer = rand() % playerTotal + 1;
                combatRollEnemy = rand() % enemyTotal + 1;

//                cout << combatTotal << "\n";
//                cout << enemyTotal << "\n";
//                cout << playerTotal << "\n";

                cout << "Player rolled: " << combatRollPlayer << "\n";
                cout << "Enemy rolled: " << combatRollEnemy << "\n\n";

                if (combatRollPlayer > combatRollEnemy) //HIT
                {
                    cout << "Hit!" << "\n\n";
                    damage = character.getDamage();
                    enemies[choice].takeDamage(damage);

                    cout << damage << " damage dealt!" << "\n\n";

                    if (!enemies[choice].isAlive())
                    {
                        gainExp = enemies[choice].getExp();
                        character.gainExp(gainExp);
                        gainGold = enemies[choice].getGold();
                        character.gainGold(gainGold);
                        cout << "Enemy defeated! Gained " << gainExp << " experience!" << "\n";
                        cout << "You gained " << gainGold << " gold!" << "\n\n";
                        enemies.remove(choice);

//                      Item roll
                        int roll = rand() % 100 + 1;
                        int rarity = -1;

                        if (roll > 20)
                        {
                            rarity = 0;
                            if (roll > 30)
                            {
                                rarity = 1;
                                if (roll > 60)
                                {
                                    rarity = 2;
                                    if (roll > 85)
                                    {
                                        rarity = 3;
                                        if (roll > 95)
                                            rarity = 4;
                                    }
                                }
                            }
                        }
                        if (roll >= 0)
                        {
                            roll = rand() % 100 + 1;
                            if (roll > 50)
                            {
                                Weapon tempW(character.getLevel() + rand() % 3, rand()%5);
                                character.addItem(tempW);
                                cout << "Enemy dropped a weapon!" << "\n";
                            }
                            else
                            {
                                Armor tempA(character.getLevel() + rand() % 3, rand()%5);
                                character.addItem(tempA);
                                cout << "Enemy dropped an armor!" << "\n";
                            }
                        }
                    }
                }
                else //MISS
                {
                    cout << "You missed!" << "\n\n";
                }
                    break;
                case 2: //DEFEND
                    break;
                case 3: //USE ITEM
                    break;
                default:
                    break;
            }

            playerTurn = false;
        }
        else if (!playerTurn && !playerDefeated && !escape && !enemiesDefeated)
        {
            cout << "-=ENEMY TURN!=-" << "\n";
            cout << "Continue.." << "\n\n";
            cin.get();

            for (size_t i = 0; i < enemies.size(); i++)
            {
                combatTotal = enemies[i].getAccuracy() + character.getDefenceMax();
                enemyTotal = enemies[i].getAccuracy() / (double)combatTotal * 100;
                playerTotal = character.getDefenceMax() / (double)combatTotal * 100;
                combatRollPlayer = rand() % playerTotal + 1;
                combatRollEnemy = rand() % enemyTotal + 1;

                cout << "Enemy: " << i << "\n\n";
                cout << "Player rolled: " << combatRollPlayer << "\n";
                cout << "Enemy rolled: " << combatRollEnemy << "\n\n";

                if (combatRollPlayer < combatRollEnemy) //HIT
                {
                    cout << "Hit!" << "\n\n";
                    damage = enemies[i].getDamage();
                    character.takeDamage(damage);

                    cout << damage << " damage dealt!" << "\n";
                    cout << "Your Hp: " <<
                         character.getHp() << "/" << character.getHpMax() << ". \n\n";

                    if (!character.isAlive())
                    {
                        for (size_t i = 0; i < enemies.size(); i++)
                        {
                            enemies.remove(i);
                        }
                        cout << "YOU ARE DEFEATED!" << "\n\n";
                        playerDefeated = true;
                    }
                }
                else //MISS
                {
                    cout << "Enemy missed!" << "\n\n";
                }
                cout << "Continue.." << "\n\n";
                cin.get();
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
            int gainExp = chances * (rand() % 5 + 5);
            character.gainExp(gainExp);
            int gainGold = chances * (rand() % 5 + 5);
            character.gainGold(gainGold);
            cout << "You gained " << gainExp << " EXP and " << gainGold << " gold!" << "\n";
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

void Event::shopEncounter(Character &character)
{
    int choice = 0;
    bool shopping = true;

    //merchant inventory
    Inventory merchInv;
    string inv;
    int nrOfItems = rand() % 4 + 3;
    int coinToss = 0;

    for (size_t i = 0; i < nrOfItems; i++)
    {
        coinToss = rand() % 100 + 1;
        if (coinToss > 50)
            merchInv.addItem(Weapon(character.getLevel(), rand() % 5));
        else
            merchInv.addItem(Armor(character.getLevel(), rand() % 5));
    }

    for (size_t i = 0; i < merchInv.size(); i++)
    {
        inv += to_string(i) + ": " + merchInv[i].toString() + "\n" +
               " PRICE:" + to_string(merchInv[i].getBuyValue()) + "\n";
    }

    while (shopping) {
        cout << "-=Shop menu=-" << "\n\n";
        cout << "Your gold: " << character.getGold() << ". \n\n";
        cout << "0: Leave" << "\n";
        cout << "1: Buy" << "\n";
        cout << "2: Sell" << "\n";
        cout << "\n";
        cout << "Choose your action: ";
        cin >> choice;

        while (cin.fail() || choice > 3 || choice < 0) {
            //system("CLS");
            cout << "Faulty input!" << "\n";
            cin.clear();
            cin.ignore(100, '\n');

            cout << "Choose your action: ";
            cin >> choice;
        }

        cin.ignore(100, '\n');
        cout << "\n";

        switch (choice) {
            case 0: //leave the shop
                for (size_t i = 0; i < merchInv.size(); i++)
                {
                    merchInv.removeItem(i);
                }
                shopping = false;
                break;
            case 1: //buy

                cout << "-=BUY MENU=-" << "\n\n";
                cout << "Your gold: " << character.getGold() << ". \n\n";

                cout << inv << "\n";

                cout << "Choose the item you want to buy (-1 to cancel): ";
                cin >> choice;

                while (cin.fail() || choice > merchInv.size() || choice < -1) {
                    //system("CLS");
                    cout << "Faulty input!" << "\n";
                    cin.clear();
                    cin.ignore(100, '\n');

                    cout << "Choose the item you want to buy (-1 to cancel): ";
                    cin >> choice;
                }
                cin.ignore(100, '\n');
                cout << "\n";

                if (choice == -1)
                {
                    cout << "Trade has been cancelled!" << "\n";
                }
                else if (character.getGold() >= merchInv[choice].getBuyValue())
                {
                    character.payGold(merchInv[choice].getBuyValue());
                    character.addItem(merchInv[choice]);

                    cout << "You have bought " << merchInv[choice].getName() << " for "
                         << merchInv[choice].getBuyValue() << " gold." << "\n";
                    cout << "Current gold balance: " << character.getGold() << ". \n\n";

                    merchInv.removeItem(choice);
                    inv.clear();

                    for (size_t i = 0; i < merchInv.size(); i++)
                    {
                        inv += to_string(i) + ": " + merchInv[i].toString() + "\n" +
                               " PRICE:" + to_string(merchInv[i].getBuyValue()) + "\n";
                    }
                }
                else
                {
                    cout << "You can not afford that item." << "\n";
                }
                break;
            case 2: //sell
                if (character.getInvSize() > 0) {
                    cout << character.getInvAsString(true) << "\n";

                    cout << "-=SELL MENU=-" << "\n\n";
                    cout << "Your gold: " << character.getGold() << ". \n\n";

                    cout << "Choose the item you want to sell (-1 to cancel): ";
                    cin >> choice;

                    while (cin.fail() || choice > character.getInvSize() || choice < -1) {
                        //system("CLS");
                        cout << "Faulty input!" << "\n";
                        cin.clear();
                        cin.ignore(100, '\n');

                        cout << "Choose the item you want to sell (-1 to cancel): ";
                        cin >> choice;
                    }
                    cin.ignore(100, '\n');
                    cout << "\n";

                    if (choice == -1)
                    {
                        cout << "Trade has been cancelled!" << "\n";
                    }
                    else
                    {
                        int goldEarned = character.getItem(choice).getSellValue();
                        character.gainGold(goldEarned);
                        cout << "Item has been sold. Gained " << goldEarned << " gold." << "\n\n";

                        character.removeItem(choice);
                    }
                }
                else
                {
                    cout << "You have nothing to sell." << "\n";
                }
                break;
            default:
                break;
        }
        cout << "ENTER to continue..." << "\n";
        cin.get();
    }
    cout << "You left the shop." << "\n\n";
}