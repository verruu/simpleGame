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
    cout << gui::menu_divider();
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
        stringstream menu_str;

        menu_str << gui::menu_title("MAIN MENU");
        menu_str << gui::menu_divider();

        menu_str << "ACTIVE CHARACTER: " << "Nr " <<
             this->activeCharacter + 1 << "/" << this->characters.size() <<
             " - " << this->characters[activeCharacter].getCharBar() << ".\n\n";
        menu_str << gui::menu_divider();

        if (this->characters[activeCharacter].getExp() >=
            this->characters[activeCharacter].getExpNext())
        {
            menu_str << gui::alert("LEVEL UP AVAILABLE!");
            menu_str << gui::menu_divider();
        }

        menu_str << gui::menu_item(0, "Quit");
        menu_str << gui::menu_item(1, "Travel");
        menu_str << gui::menu_item(2, "Shop");
        menu_str << gui::menu_item(3, "Level Up");
        menu_str << gui::menu_item(4, "Rest");
        menu_str << gui::menu_item(5, "Character menu");
        menu_str << gui::menu_item(6, "Create a new character");
        menu_str << gui::menu_item(7, "Select a character");
        menu_str << gui::menu_item(8, "Save characters");
        menu_str << gui::menu_item(9, "Load characters");
        menu_str << "\n";

        getChoice(this->choice, menu_str.str(), 1);

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
                cout << "ERROR: MENU OPTION NON EXISTENT!" << "\n\n";
                cout << gui::menu_divider();
                break;
        }
        cout << "ENTER to continue...";
        cin.get();
        cout << "\n" << gui::menu_divider();
    }
    else
    {
        cout << "YOU HAVE DIED!" << "\n\n";
        cout << "CONTINUE?" << "\n\n";
        cout << "(0) Yes / (1) No: ";
        cin >> this->choice;

        while (cin.fail() || this->choice < 0 || this->choice > 1)
        {
            cout << "Faulty input!" << "\n";
            cin.clear();
            cin.ignore(100, '\n');

            cout << "CONTINUE?" << "\n";
            cout << "(0) Yes / (1) No: ";
            cin >> this->choice;
        }

        cin.ignore(100, '\n');
        cout << "\n";
        cout << gui::menu_divider();

        if (this->choice == 0)
            this->loadCharacters();
        else
            playing = false;
    }
}

void Game::characterMenu()
{
    bool character = true;

    while (character) {
        cout << gui::menu_title("CHARACTER MENU");
        cout << gui::menu_divider();

        cout << gui::menu_item(0, "Return to Main Menu");
        cout << gui::menu_item(1, "Show character stats");
        cout << gui::menu_item(2, "Show inventory");
        cout << gui::menu_item(3, "Equip item");
        cout << "\n";

        cout << "Choice: ";
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
        cout << gui::menu_divider();

        switch (this->choice)
        {
            case 0: //BACK
            character = false;
            cout << "Returning to main menu." << "\n\n";
                break;
            case 1: //STATS
                this->characters[this->activeCharacter].printStats();
                break;
            case 2: //INVENTORY
                cout << this->characters[this->activeCharacter].getInvAsString() << "\n";
                break;
            case 3: //EQUIP
                cout << this->characters[this->activeCharacter].getInvAsString() << "\n";
                cout << "Choose an item to equip (-1 to cancel): ";
                cin >> this->choice;

                while (cin.fail() || this->choice < -1 || this->choice >= this->characters[this->activeCharacter].getInvSize())
                {
                    cout << "Faulty input!" << "\n";
                    cin.clear();
                    cin.ignore(100, '\n');

                    cout << "\n" << "Choose an item to equip: ";
                    cin >> this->choice;
                }
                cin.ignore(100, '\n');
                cout << "\n";
                cout << gui::menu_divider();

                if (choice == -1)
                {
                    cout << "Equip operation has been cancelled!" << "\n\n";
                }
                else
                {
                    this->characters[this->activeCharacter].eqItem(this->choice);
                    cout << "Item has been equipped!" << "\n\n";
                }
                break;
            default:
                break;
        }
        cout << gui::menu_divider();
        if (this->choice > 0)
        {
            cout << "ENTER to continue...";
            cin.get();
            cout << "\n" << gui::menu_divider();
        }
    }
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
            cout << "\n" << "Error! Character already exists!" << "\n\n";
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
        cout << gui::menu_divider();
        cout << "Which stat do you want to upgrade?" << "\n\n";
        cout << gui::menu_item(0, "Strength");
        cout << gui::menu_item(1, "Vitality");
        cout << gui::menu_item(2, "Dexterity");
        cout << gui::menu_item(3, "Intelligence");
        cout << "\n";
        cout << "Choice: ";
        cin >> this->choice;

        while (cin.fail() || this->choice > 3)
        {
            cout << "Faulty input!" << "\n";
            cin.clear();
            cin.ignore(100, '\n');

            cout << "Which stat do you want to upgrade?";
            cin >> this->choice;
        }

        cin.ignore(100, '\n');
        cout << "\n";
        cout << gui::menu_divider();

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
    cout << "Save successful!" << "\n\n";
    cout << gui::menu_divider();
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
    int flasks = 0;
    int flaskShards = 0;

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
            str >> flasks;
            str >> flaskShards;
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
                           exp, flasks, flaskShards, strength, vitality, dexterity,
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
            cout << "Character " << temp.getName() << " loaded successfully!" << "\n\n";
            str.clear();
        }
    }
    inFile.close();
    cout << gui::menu_divider();

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

        cout << "Select character: ";
        cin >> this->choice;
        cout << "\n";
    }

    cin.ignore(100, '\n');
    cout << "\n";
    cout << gui::menu_divider();

    this->activeCharacter = this->choice;
    cout << this->characters[this->activeCharacter].getName() << " selected!" << "\n\n";
    cout << gui::menu_divider();

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

    cout << gui::menu_title("REST");
    cout << gui::menu_divider();

    cout << "You have " << currHp << "/" << maxHp << " Hp." << "\n";


    if (restCost > charGold)
    {
        cout << "You have " << charGold << " gold." << "\n";
        cout << "Resting will cost you " << restCost << " gold." << "\n";
        cout << "Not enough gold!"  << "\n";
    }
    else if (currHp >= maxHp)
    {
        cout << "You are well rested already." << "\n\n";
        cout << gui::menu_divider();
    }
    else
    {
        cout << "You have " << charGold << " gold." << "\n";
        cout << "Resting will cost you " << restCost << " gold." << "\n";
        cout << "Do you want to rest? (1) Yes, (0) No: ";
        cin >> this->choice;

        while (cin.fail() || this->choice > 1 || this->choice < 0) {
            cout << "Faulty input!" << "\n";
            cin.clear();
            cin.ignore(100, '\n');

            cout << "Do you want to rest? (1) Yes, (0) No: ";
            cin >> this->choice;
        }
        cin.ignore(100, '\n');
        cout << "\n";
        cout << gui::menu_divider();

        if (this->choice == 1)
        {
            this->characters[this->activeCharacter].resetHp();
            this->characters[this->activeCharacter].payGold(restCost);
            int goldBalance = this->characters[this->activeCharacter].getGold();
            cout << "Your Hp has been restored to maximum. Current gold balance: " << goldBalance << "\n\n";
        }
        cout << gui::menu_divider();
    }
}