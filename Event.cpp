#include "Header-files/Event.h"

int Event::nrOfEvents = 4;

Event::Event()
{

}

Event::~Event()
{

}

void Event::generateEvent(Character &character, dArr<Enemy>& enemies)
{
    int i = rand() % Event::nrOfEvents;
//int i = 3;

    switch (i)
    {
        case 0:
            cout << gui::menu_title("ENEMY ATTACK!");
            cout << gui::menu_divider();
            this->enemyEncounter(character, enemies);
            break;
        case 1:
            cout << "You've got a puzzle to solve!" << "\n\n";
            cout << gui::menu_divider();
            this->puzzleEncounter(character);
            break;
        case 2:
            cout << "You've found a wandering merchant who wants to trade with you.\n\n";
            cout << gui::menu_divider();
            this->shopEncounter(character);
            break;
        case 3:
            cout << "Prepare for a BOSS encounter!\n";
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
    int coinToss = rand() % 2;

    if (coinToss == 1)
        playerTurn = true;
    else
        playerTurn = false;

    //End encounter conditions
    bool escape = false;
    bool playerDefeated = false;
    bool enemiesDefeated = false;

    //Enemies
    enemies.clear();
    int nrOfEnemies = rand() % 5 + 1;

    for (size_t i = 0; i < nrOfEnemies; i++)
    {
        enemies.push(Enemy(character.getLevel() + rand() % 3));
    }

    for (size_t i = 0; i < enemies.size(); i++)
    {
        cout << i << ": " << enemies[i].getAsStringEvent() << "\n";
    }
    cout << "\n";
    cout << gui::menu_divider();

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
            stringstream menu_str;

            cout << gui::menu_title("PLAYER TURN");
            cout << gui::menu_divider();
            cout << "Continue..";
            cin.get();
            cout << "\n" << gui::menu_divider();

            menu_str << gui::menu_title("BATTLE MENU");
            menu_str << gui::menu_divider();
            menu_str << "Your Hp: " <<
            character.getHp() << "/" << character.getHpMax() << ". \n\n";
            menu_str << gui::menu_item(0, "Escape");
            menu_str << gui::menu_item(1, "Attack");
            menu_str << gui::menu_item(2, "Defend");
            menu_str << gui::menu_item(3, "Use item");
            menu_str << "\n";

            getChoice(choice, menu_str.str(), 1);

            switch (choice)
            {
                case 0: //ESCAPE
                cout << "You have escaped the battle successfully!" << "\n\n";
                cout << gui::menu_divider();
                escape = true;
                    break;
                case 1: //ATTACK
                menu_str.clear();
                //Enemy selection
                    menu_str << "Select enemy: " << "\n\n";

                    for (size_t i = 0; i < enemies.size(); i++)
                    {
                        menu_str << gui::menu_item(i, enemies[i].getAsStringEvent());
                    }
                    menu_str << "\n";

                    getChoice(choice, menu_str.str(), 1);

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
                        if (rarity >= 0)
                        {
                            roll = rand() % 100 + 1;
                            if (roll > 50)
                            {
                                Weapon tempW(character.getLevel() + rand() % 3, rarity);
                                character.addItem(tempW);
                                cout << "Enemy dropped a weapon!" << "\n";
                            }
                            else
                            {
                                Armor tempA(character.getLevel() + rand() % 3, rarity);
                                character.addItem(tempA);
                                cout << "Enemy dropped an armor!" << "\n";
                            }
                        }
                    }
                    cout << "\n" << gui::menu_divider();
                }
                else //MISS
                {
                    cout << "You missed!" << "\n\n";
                    cout << gui::menu_divider();
                }
                    playerTurn = false;
                    break;
                case 2: //DEFEND
                    playerTurn = false;
                    break;
                case 3: //USE ITEM
                    playerTurn = false;
                    break;
                default:
                    cout << "ERROR: MENU OPTION NON EXISTENT!" << "\n\n";
                    cout << gui::menu_divider();
                    break;
            }
        }
        else if (!playerTurn && !playerDefeated && !escape && !enemiesDefeated)
        {
            cout << gui::menu_title("ENEMY TURN");
            cout << gui::menu_divider();
            cout << "Continue..";
            cin.get();
            cout << "\n" << gui::menu_divider();

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
                        cout << "YOU ARE DEFEATED!" << "\n\n";
                        playerDefeated = true;
                    }
                }
                else //MISS
                {
                    cout << "Enemy missed!" << "\n\n";
                }
                cout << "Continue..";
                cin.get();
                cout << "\n" << gui::menu_divider();
            }
//            cout << "\n" << gui::menu_divider();
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
        cout << gui::menu_divider();
        cout << puzzle.getAsString();

        cout << "\n" << "Your answer: ";
        cin >> userAns;

        while (cin.fail())
        {
            cout << "Faulty input!" << "\n";
            cin.clear();
            cin.ignore(100, '\n');

            cout << "\n" << "Your answer: ";
            cin >> userAns;
        }

        cin.ignore(100, '\n');
        cout << "\n";
        cout << gui::menu_divider();

        if (puzzle.getCorrectAns() == userAns)
        {
            completed = true;
            int gainExp = chances * (rand() % 5 + 5);
            character.gainExp(gainExp);
            int gainGold = chances * (rand() % 5 + 5);
            character.gainGold(gainGold);
            cout << "CONGRATZ! YOU HAVE SUCCEEDED! \n\n";
            cout << "You gained " << gainExp << " EXP and " << gainGold << " gold!" << "\n";
        }
        chances--;
    }
    if (completed)
    {
        cout << "\n" << gui::menu_divider();
    } else {
        cout << "YOU FAILED BRAH! \n\n";
        cout << gui::menu_divider();
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
        cout << gui::menu_title("SHOP MENU");
        cout << gui::menu_divider();
        cout << "Your gold: " << character.getGold() << ". \n\n";
        cout << gui::menu_item(0, "Leave");
        cout << gui::menu_item(1, "Buy");
        cout << gui::menu_item(2, "Sell");
        cout << "\n";
        cout << "Choose your action: ";
        cin >> choice;

        while (cin.fail() || choice > 3 || choice < 0) {
            //system("CLS");
            cout << "Faulty input!" << "\n";
            cin.clear();
            cin.ignore(100, '\n');

            cout << "\n" << "Choose your action: ";
            cin >> choice;
        }

        cin.ignore(100, '\n');
        cout << "\n";
        cout << gui::menu_divider();

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
                cout << gui::menu_divider();
                cout << "Your gold: " << character.getGold() << ". \n\n";

                cout << inv << "\n";

                cout << "Choose the item you want to buy (-1 to cancel): ";
                cin >> choice;

                while (cin.fail() || choice > merchInv.size() || choice < -1) {
                    //system("CLS");
                    cout << "Faulty input!" << "\n";
                    cin.clear();
                    cin.ignore(100, '\n');

                    cout << "\n" << "Choose the item you want to buy (-1 to cancel): ";
                    cin >> choice;
                }
                cin.ignore(100, '\n');
                cout << "\n";
                cout << gui::menu_divider();

                if (choice == -1)
                {
                    cout << "Trade has been cancelled!" << "\n";
                    cout << "\n" << gui::menu_divider();
                }
                else if (character.getGold() >= merchInv[choice].getBuyValue())
                {
                    character.payGold(merchInv[choice].getBuyValue());
                    character.addItem(merchInv[choice]);

                    cout << "You have bought " << merchInv[choice].getName() << " for "
                         << merchInv[choice].getBuyValue() << " gold." << "\n";
                    cout << "Current gold balance: " << character.getGold() << ". \n";
                    cout << "\n" << gui::menu_divider();

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
                    cout << "\n" << gui::menu_divider();
                }
                break;
            case 2: //sell
                if (character.getInvSize() > 0) {
                    cout << "-=SELL MENU=-" << "\n\n";
                    cout << "Your gold: " << character.getGold() << ". \n\n";
                    cout << character.getInvAsString(true) << "\n";

                    cout << "Choose the item you want to sell (-1 to cancel): ";
                    cin >> choice;

                    while (cin.fail() || choice > character.getInvSize() || choice < -1) {
                        //system("CLS");
                        cout << "Faulty input!" << "\n";
                        cin.clear();
                        cin.ignore(100, '\n');

                        cout << "\n" << "Choose the item you want to sell (-1 to cancel): ";
                        cin >> choice;
                    }
                    cin.ignore(100, '\n');
                    cout << "\n";
                    cout << gui::menu_divider();

                    if (choice == -1)
                    {
                        cout << "Trade has been cancelled!" << "\n";
                        cout << "\n" << gui::menu_divider();
                    }
                    else
                    {
                        int goldEarned = character.getItem(choice).getSellValue();
                        character.gainGold(goldEarned);
                        cout << "Item has been sold. Gained " << goldEarned << " gold." << "\n\n";
                        cout << gui::menu_divider();
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
        cout << "ENTER to continue...";
        cin.get();
        cout << "\n" << gui::menu_divider();
    }
    cout << "You left the shop." << "\n";
    cout << "\n" << gui::menu_divider();
}

//void Event::bossEncounter(Character &character, Boss &boss)
//{
//    bool playerTurn = false;
//    int choice = 0;
//
//    //Coin toss for turn
//    int coinToss = rand() % 2;
//
//    if (coinToss == 1)
//        playerTurn = true;
//    else
//        playerTurn = false;
//
//    //End encounter conditions
//    bool escape = false;
//    bool playerDefeated = false;
//    bool enemiesDefeated = false;
//
//    //Enemies
//    int nrOfEnemies = rand() % 5 + 1;
//
//    for (size_t i = 0; i < nrOfEnemies; i++)
//    {
//        enemies.push(Enemy(character.getLevel() + rand() % 3));
//    }
//
//    for (size_t i = 0; i < enemies.size(); i++)
//    {
//        cout << i << ": " << "Level: " << enemies[i].getLevel() <<
//             " HP: " << enemies[i].getHp() << "/" << enemies[i].getHpMax() <<
//             " Defence: " << enemies[i].getDefence() << " Accuracy: " <<
//             enemies[i].getAccuracy() <<
//             " Damage: " << enemies[i].getDamageMin() << " - " << enemies[i].getDamageMax() << "\n";
//    }
//    cout << "\n";
//    cout << gui::menu_divider();
//
//    //Battle variables and modifiers
//    int damage = 0;
//    int gainExp = 0;
//    int gainGold = 0;
//    int playerTotal = 0;
//    int enemyTotal = 0;
//    int combatTotal = 0;
//    int combatRollPlayer = 0;
//    int combatRollEnemy = 0;
//
//    while(!escape && !playerDefeated && !enemiesDefeated)
//    {
//        if (playerTurn && !playerDefeated)
//        {
//            cout << gui::menu_title("PLAYER TURN");
//            cout << gui::menu_divider();
//            cout << "Continue..";
//            cin.get();
//            cout << "\n" << gui::menu_divider();
//
//            cout << gui::menu_title("BATTLE MENU");
//            cout << gui::menu_divider();
//            cout << "Your Hp: " <<
//            character.getHp() << "/" << character.getHpMax() << ". \n\n";
//            cout << gui::menu_item(0, "Escape");
//            cout << gui::menu_item(1, "Attack");
//            cout << gui::menu_item(2, "Defend");
//            cout << gui::menu_item(3, "Use item");
//            cout << "\n";
//            cout << "Choose your action: ";
//            cin >> choice;
//
//            while (cin.fail() || choice > 3 || choice < 0)
//            {
//                //system("CLS");
//                cout << "Faulty input!" << "\n";
//                cin.clear();
//                cin.ignore(100, '\n');
//
//                cout << "\n" << "Choose your action: ";
//                cin >> choice;
//            }
//            cin.ignore(100, '\n');
//            cout << "\n";
//            cout << gui::menu_divider();
//
//            switch (choice)
//            {
//                case 0: //ESCAPE
//                for (size_t i = 0; i < enemies.size(); i++)
//                {
//                    enemies.remove(i);
//                }
//                cout << "You have escaped the battle successfully!" << "\n\n";
//                cout << gui::menu_divider();
//                escape = true;
//                    break;
//                case 1: //ATTACK
//
//                //Enemy selection
//                    cout << "Select enemy: " << "\n\n";
//
//                    for (size_t i = 0; i < enemies.size(); i++)
//                    {
//                        cout << i << ": " << "Level: " << enemies[i].getLevel() <<
//                        " HP: " << enemies[i].getHp() << "/" << enemies[i].getHpMax() <<
//                        " Defence: " << enemies[i].getDefence() << " Accuracy: " <<
//                        enemies[i].getAccuracy() <<
//                        " Damage: " << enemies[i].getDamageMin() << " - " << enemies[i].getDamageMax() << "\n";
//                    }
//
//                    cout << "\n";
//                    cout << "Choice: ";
//                    cin >> choice;
//
//                    while (cin.fail() || choice >= enemies.size() || choice < 0)
//                    {
//                        //system("CLS");
//                        cout << "Faulty input!" << "\n";
//                        cin.clear();
//                        cin.ignore(100, '\n');
//
//                        cout << "\n" << "Select enemy: ";
//                        cin >> choice;
//                    }
//
//                    cin.ignore(100, '\n');
//                    cout << "\n";
//                    cout << gui::menu_divider();
//
//                //Attack roll
//                combatRollPlayer = rand() % 100 + 1;
//
//                combatTotal = enemies[choice].getDefence() + character.getAccuracy();
//                enemyTotal = enemies[choice].getDefence() / (double)combatTotal * 100;
//                playerTotal = character.getAccuracy() / (double)combatTotal * 100;
//                combatRollPlayer = rand() % playerTotal + 1;
//                combatRollEnemy = rand() % enemyTotal + 1;
//
////                cout << combatTotal << "\n";
////                cout << enemyTotal << "\n";
////                cout << playerTotal << "\n";
//
//                cout << "Player rolled: " << combatRollPlayer << "\n";
//                cout << "Enemy rolled: " << combatRollEnemy << "\n\n";
//
//                if (combatRollPlayer > combatRollEnemy) //HIT
//                {
//                    cout << "Hit!" << "\n\n";
//                    damage = character.getDamage();
//                    enemies[choice].takeDamage(damage);
//
//                    cout << damage << " damage dealt!" << "\n\n";
//
//                    if (!enemies[choice].isAlive())
//                    {
//                        gainExp = enemies[choice].getExp();
//                        character.gainExp(gainExp);
//                        gainGold = enemies[choice].getGold();
//                        character.gainGold(gainGold);
//                        cout << "Enemy defeated! Gained " << gainExp << " experience!" << "\n";
//                        cout << "You gained " << gainGold << " gold!" << "\n\n";
//                        enemies.remove(choice);
//
////                      Item roll
//                        int roll = rand() % 100 + 1;
//                        int rarity = -1;
//
//                        if (roll > 20)
//                        {
//                            rarity = 0;
//                            if (roll > 30)
//                            {
//                                rarity = 1;
//                                if (roll > 60)
//                                {
//                                    rarity = 2;
//                                    if (roll > 85)
//                                    {
//                                        rarity = 3;
//                                        if (roll > 95)
//                                            rarity = 4;
//                                    }
//                                }
//                            }
//                        }
//                        if (rarity >= 0)
//                        {
//                            roll = rand() % 100 + 1;
//                            if (roll > 50)
//                            {
//                                Weapon tempW(character.getLevel() + rand() % 3, rarity);
//                                character.addItem(tempW);
//                                cout << "Enemy dropped a weapon!" << "\n";
//                            }
//                            else
//                            {
//                                Armor tempA(character.getLevel() + rand() % 3, rarity);
//                                character.addItem(tempA);
//                                cout << "Enemy dropped an armor!" << "\n";
//                            }
//                        }
//                    }
//                    cout << "\n" << gui::menu_divider();
//                }
//                else //MISS
//                {
//                    cout << "You missed!" << "\n\n";
//                    cout << gui::menu_divider();
//                }
//                    break;
//                case 2: //DEFEND
//                    break;
//                case 3: //USE ITEM
//                    break;
//                default:
//                    break;
//            }
////            cout << "\n" << gui::menu_divider();
//            playerTurn = false;
//        }
//        else if (!playerTurn && !playerDefeated && !escape && !enemiesDefeated)
//        {
//            cout << gui::menu_title("ENEMY TURN");
//            cout << gui::menu_divider();
//            cout << "Continue..";
//            cin.get();
//            cout << "\n" << gui::menu_divider();
//
//            for (size_t i = 0; i < enemies.size(); i++)
//            {
//                combatTotal = enemies[i].getAccuracy() + character.getDefenceMax();
//                enemyTotal = enemies[i].getAccuracy() / (double)combatTotal * 100;
//                playerTotal = character.getDefenceMax() / (double)combatTotal * 100;
//                combatRollPlayer = rand() % playerTotal + 1;
//                combatRollEnemy = rand() % enemyTotal + 1;
//
//                cout << "Enemy: " << i << "\n\n";
//                cout << "Player rolled: " << combatRollPlayer << "\n";
//                cout << "Enemy rolled: " << combatRollEnemy << "\n\n";
//
//                if (combatRollPlayer < combatRollEnemy) //HIT
//                {
//                    cout << "Hit!" << "\n\n";
//                    damage = enemies[i].getDamage();
//                    character.takeDamage(damage);
//
//                    cout << damage << " damage dealt!" << "\n";
//                    cout << "Your Hp: " <<
//                         character.getHp() << "/" << character.getHpMax() << ". \n\n";
//
//                    if (!character.isAlive())
//                    {
//                        for (size_t i = 0; i < enemies.size(); i++)
//                        {
//                            enemies.remove(i);
//                        }
//                        cout << "YOU ARE DEFEATED!" << "\n\n";
//                        playerDefeated = true;
//                    }
//                }
//                else //MISS
//                {
//                    cout << "Enemy missed!" << "\n\n";
//                }
//                cout << "Continue..";
//                cin.get();
//                cout << "\n" << gui::menu_divider();
//            }
////            cout << "\n" << gui::menu_divider();
//            playerTurn = true;
//        }
//
//        if (!character.isAlive())
//        {
//            playerDefeated = true;
//        }
//
//        else if (enemies.size() <= 0)
//        {
//            enemiesDefeated = true;
//        }
//    }
//}