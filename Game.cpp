#include "Header-files/Game.h"

Game::Game()
{
    choice = 0;
    playing = true;
    activeCharacter = 0;
    fileName = "Characters.txt";
}

Game::~Game()
{

}

//functions
void Game::initGame()
{
    ifstream in;
    in.open("characters.txt");

    Weapon::initNames();
    Armor::initNames();

    if (in.is_open())
        this->loadCharacters();
    else
    {
        createNewCharacter();
        this->saveCharacters();
    }
    in.close();
}

void Game::mainMenu()
{
    if (this->characters[activeCharacter].isAlive())
    {
        cout << " -=MAIN MENU=- " << "\n\n";

        cout << "ACTIVE CHARACTER: " <<
             this->characters[activeCharacter].getName() << ". Nr " <<
             this->activeCharacter + 1 << "/" << this->characters.size() << ".\n\n";

        if (this->characters[activeCharacter].getExp() >=
            this->characters[activeCharacter].getExpNext())
        {
            cout << "LEVEL UP AVAILABLE!" << "\n\n";
        }

        cout << "0: Quit" << "\n";
        cout << "1: Travel" << "\n";
        cout << "2: Shop" << "\n";
        cout << "3: Level up" << "\n";
        cout << "4: Rest" << "\n";
        cout << "5: Character menu" << "\n";
        cout << "6: Create a new character" << "\n";
        cout << "7: Select a character" << "\n";
        cout << "8: Save characters" << "\n";
        cout << "9: Load characters" << "\n";
        cout << "\n";

        cout << "\n" << "Choice: ";
        cin >> this->choice;

        while (cin.fail()) {
            cout << "Faulty input!" << "\n";
            cin.clear();
            cin.ignore(100, '\n');

            cout << "\n" << "Choice: ";
            cin >> this->choice;
        }

        cin.ignore(100, '\n');
        cout << "\n";

        switch (choice) {
            case 0: //QUIT
                playing = false;
                break;
            case 1: //TRAVEL
                Travel();
                break;
            case 2: //SHOP
                break;
            case 3: //LEVEL UP
                this->levelUpCharacter();
                break;
            case 4: //REST
                rest();
                break;
            case 5: //CHARACTER SHEET
                this->characterMenu();
                break;
            case 6: //CREATE A NEW CHARACTER
                createNewCharacter();
                saveCharacters();
                break;
            case 7: //SELECT A CHARACTER
                selectCharacter();
                break;
            case 8: //SAVE CHARACTERS
                saveCharacters();
                break;
            case 9: //LOAD CHARACTERS
                loadCharacters();
                break;
            default:
                break;
        }
        cout << "ENTER to continue..." << "\n";
        cin.get();
    }
    else
    {
        cout << "YOU HAVE DIED!" << "\n" << "CONTINUE?" << "\n";
        cout << "(0) Yes / (1) No" << "\n";
        cin >> this->choice;

        while (cin.fail() || this->choice < 0 || this->choice > 1)
        {
            cout << "Faulty input!" << "\n";
            cin.clear();
            cin.ignore(100, '\n');

            cout << "(0) Yes / (1) No" << "\n";
            cin >> this->choice;
        }

        cin.ignore(100, '\n');
        cout << "\n";

        if (this->choice == 0)
            this->loadCharacters();
        else
            playing = false;
    }
}

void Game::characterMenu()
{
    do {
        cout << " -=CHARACTER MENU=- " << "\n\n";

        cout << "0: Return to Main Menu" << "\n";
        cout << "1: Show character stats" << "\n";
        cout << "2: Show inventory" << "\n";
        cout << "3: Equip item" << "\n";

        cout << "\n" << "Choice: ";
        cin >> this->choice;

        while (cin.fail() || this->choice < 0 || this->choice > 3)
        {
            cout << "Faulty input!" << "\n";
            cin.clear();
            cin.ignore(100, '\n');

            cout << "\n" << "Choice: ";
            cin >> this->choice;
        }

        cin.ignore(100, '\n');
        cout << "\n";

        switch (this->choice) {
            case 1: //STATS
                this->characters[this->activeCharacter].printStats();
                break;
            case 2: //INVENTORY
                cout << this->characters[this->activeCharacter].getInvAsString();
                break;
            case 3: //EQUIP
                cout << "\n" << "Choose an item to equip: ";
                cin >> this->choice;

                while (cin.fail() || this->choice < 0 || this->choice >= this->characters[this->activeCharacter].getInvSize())
                {
                    cout << "Faulty input!" << "\n";
                    cin.clear();
                    cin.ignore(100, '\n');

                    cout << "\n" << "Choose an item to equip: ";
                    cin >> this->choice;
                }

                cin.ignore(100, '\n');
                cout << "\n";

                this->characters[this->activeCharacter].eqItem(this->choice);
                break;
            default:
                break;
        }
        if (this->choice > 0)
        {
            cout << "ENTER to continue..." << "\n";
            cin.get();
        }
    } while (this->choice > 0);
}

void Game::createNewCharacter()
{
    string name = "";
    cout << "Enter your character name: ";
    getline(cin, name);

    for (size_t i = 0; i < this->characters.size(); i++)
    {
        while (name == this->characters[i].getName())
        {
            cout << "Error! Character already exists!" << "\n";
            cout << "Enter your character name: ";
            getline(cin, name);
        }
    }

    characters.push_back(Character());
    activeCharacter = characters.size() -1;
    characters[activeCharacter].initialize(name);
}

void Game::levelUpCharacter()
{
    this->characters[activeCharacter].levelUp();

    if (this->characters[activeCharacter].getStatPoints() > 0)
    {
        cout << "You have stat points to allocate!" << "\n\n";
        cout << "Which stat do you want to upgrade?" << "\n";
        cout << "0: Strength " << "\n";
        cout << "1: Vitality " << "\n";
        cout << "2: Dexterity " << "\n";
        cout << "3: Intelligence " << "\n";
        cin >> this->choice;

        while (cin.fail() || this->choice > 3)
        {
            cout << "Faulty input!" << "\n";
            cin.clear();
            cin.ignore(100, '\n');

            cout << "Which stat do you want to upgrade?" << "\n";
            cin >> this->choice;
        }

        cin.ignore(100, '\n');
        cout << "\n";

        switch (this->choice)
        {
            case 0: //STRENGTH
                this->characters[activeCharacter].addToStat(0, 1);
                break;
            case 1: //VITALITY
                this->characters[activeCharacter].addToStat(1, 1);
                break;
            case 2: //DEXTERITY
                this->characters[activeCharacter].addToStat(2, 1);
                break;
            case 3: //INTELLIGENCE
                this->characters[activeCharacter].addToStat(3, 1);
                break;
            default:
                break;
        }
    }
    this->characters[activeCharacter].updateStats();
}

void Game::saveCharacters()
{
    ofstream outFile(fileName);
    if (outFile.is_open())
    {
        for (size_t i = 0; i < this->characters.size(); i++)
        {
            outFile << this->characters[i].getAsString() << "\n";


            outFile << this->characters[i].getInvAsStringSave() << "\n";
        }
    }
    outFile.close();
}

void Game::loadCharacters()
{
    ifstream inFile(fileName);

    this->characters.clear();

    string name = "";
    int distanceTravelled = 0;
    int gold = 0;
    int level = 0;
    int exp = 0;

    int strength = 0;
    int vitality = 0;
    int dexterity = 0;
    int intelligence = 0;

    int hp = 0;
    int stamina = 0;

    int statPoints = 0;
    int skillPoints = 0;

    //Item
    int itemType = 0;
    int type = 0;
    int defence = 0;
    int damageMin = 0;
    int damageMax = 0;
    //name
    //level
    int buyValue = 0;
    int sellValue = 0;
    int rarity = 0;

    Inventory tempItems;

    string line = "";
    stringstream str;

    if (inFile.is_open())
    {
        while (getline(inFile, line))
        {
            str.str(line);
            str >> name;
            str >> distanceTravelled;
            str >> gold;
            str >> level;
            str >> exp;
            str >> strength;
            str >> vitality;
            str >> dexterity;
            str >> intelligence;
            str >> hp;
            str >> stamina;
            str >> statPoints;
            str >> skillPoints;

            //create character
            Character temp(name, distanceTravelled, gold, level,
                           exp, strength, vitality, dexterity,
                           intelligence, hp, stamina, statPoints,
                           skillPoints);

            //weapon
            str >> itemType >> name >> level >> rarity >>
                damageMin >> damageMax >> sellValue >> buyValue;

            Weapon weapon(damageMin, damageMax, name, level, buyValue, sellValue, rarity);

            //armor head
            str >> itemType >> name >> level >> rarity >>
                type >> defence >> sellValue >> buyValue;

            Armor armor_head(type, defence, name, level, buyValue, sellValue, rarity);

            //armor chest
            str >> itemType >> name >> level >> rarity >>
                type >> defence >> sellValue >> buyValue;

            Armor armor_chest(type, defence, name, level, buyValue, sellValue, rarity);

            //armor arms
            str >> itemType >> name >> level >> rarity >>
                type >> defence >> sellValue >> buyValue;

            Armor armor_arms(type, defence, name, level, buyValue, sellValue, rarity);

            //armor legs
            str >> itemType >> name >> level >> rarity >>
                type >> defence >> sellValue >> buyValue;

            Armor armor_legs(type, defence, name, level, buyValue, sellValue, rarity);

            temp.setWeapon(weapon);
            temp.setArmorHead(armor_head);
            temp.setArmorChest(armor_chest);
            temp.setArmorArms(armor_arms);
            temp.setArmorLegs(armor_legs);

            //add inv items
            str.clear();
            line.clear();
            getline(inFile, line);

            str.str(line);

            while (str >> itemType >> name >> level >> rarity >>
                   damageMin >> damageMax >> sellValue >> buyValue)
            {
                temp.addItem (Weapon(damageMin, damageMax, name, level,
                                          buyValue, sellValue, rarity));

            }

            str.clear();
            line.clear();
            getline(inFile, line);

            str.str(line);

            while (str >> itemType >> name >> level >> rarity >>
                          type >> defence >> sellValue >> buyValue)
            {
                temp.addItem (Armor(type, defence, name, level,
                                     buyValue, sellValue, rarity));

            }

            this->characters.push_back(Character(temp));
            cout << "Character " << temp.getName() << " loaded successfully!\n";
            str.clear();
        }
    }
    inFile.close();

    if (this->characters.size() <= 0)
    {
        throw runtime_error("Error! No characters loaded or the file is empty!");
    }
}

void Game::selectCharacter()
{
    cout << "Select character: " << "\n\n";

    for (size_t i = 0; i < this->characters.size(); i++)
    {
        cout << "Index: " << i << " = " << this->characters[i].getName() <<
        ", level: " << this->characters[i].getLevel() << "\n";
    }
    cout << "\n";
    cout << "Choice: ";
    cin >> this->choice;

    while (cin.fail() || this->choice >= this->characters.size() || this->choice < 0)
    {
        cout << "Faulty input!" << "\n";
        cin.clear();
        cin.ignore(100, '\n');

        cout << "Select character: " << "\n";
        cin >> this->choice;
    }

    cin.ignore(100, '\n');
    cout << "\n";

    this->activeCharacter = this->choice;
    cout << this->characters[this->activeCharacter].getName() << " selected!" << "\n\n";
}

void Game::Travel()
{
    this->characters[activeCharacter].travel();
    Event ev;
    ev.generateEvent(this->characters[activeCharacter], this->enemies);

}

void  Game::rest()
{
    int restCost = (this->characters[this->activeCharacter].getHpMax() - this->characters[this->activeCharacter].getHp()) * 3;
    int charGold = this->characters[this->activeCharacter].getGold();
    int currHp = this->characters[this->activeCharacter].getHp();
    int maxHp = this->characters[this->activeCharacter].getHpMax();

    cout << "-=REST=-" << "\n\n";
    cout << "You have " << currHp << "/" << maxHp << " Hp." << "\n";


    if (restCost > charGold)
    {
        cout << "You have " << charGold << " gold." << "\n";
        cout << "Resting will cost you " << restCost << " gold." << "\n";
        cout << "Not enough gold!"  << "\n";
    }
    else if (currHp >= maxHp)
    {
        cout << "You are well rested already." << "\n";
    }
    else
    {
        cout << "You have " << charGold << " gold." << "\n";
        cout << "Resting will cost you " << restCost << " gold." << "\n";
        cout << "Do you want to rest? (1) Yes, (0) No." << "\n";
        cin >> this->choice;

        while (cin.fail() || this->choice > 1 || this->choice < 0) {
            cout << "Faulty input!" << "\n";
            cin.clear();
            cin.ignore(100, '\n');

            cout << "Do you want to rest? (1) Yes, (0) No." << "\n";
            cin >> this->choice;
        }

        cin.ignore(100, '\n');
        cout << "\n";

        if (this->choice == 1)
        {
            this->characters[this->activeCharacter].resetHp();
            this->characters[this->activeCharacter].payGold(restCost);
            int goldBalance = this->characters[this->activeCharacter].getGold();
            cout << "Your Hp has been restored to maximum. Current gold balance is " << goldBalance << "\n";
        }
    }
}