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
    createNewCharacter();
}

void Game::mainMenu()
{
    cout << "ENTER to continue..." << "\n";
    cin.get();

    if (this->characters[activeCharacter].getExp() >=
        this->characters[activeCharacter].getExpNext())
    {
        cout << "LEVEL UP AVAILABLE!" << "\n\n";
    }
    cout << " -=MAIN MENU=- " << "\n\n";

    cout << "ACTIVE CHARACTER: " <<
    this->characters[activeCharacter].getName() << ". Nr " <<
    this->activeCharacter+1 << "/" << this->characters.size() << ".\n\n";

    cout << "0: Quit" << "\n";
    cout << "1: Travel" << "\n";
    cout << "2: Shop" << "\n";
    cout << "3: Level up" << "\n";
    cout << "4: Rest" << "\n";
    cout << "5: Character sheet" << "\n";
    cout << "6: Create a new character" << "\n";
    cout << "7: Select a character" << "\n";
    cout << "8: Save characters" << "\n";
    cout << "9: Load characters" << "\n";
    cout << "\n";

    cout << "\n" << "Choice: ";
    cin >> this->choice;

    while (cin.fail())
    {
        cout << "Faulty input!" << "\n";
        cin.clear();
        cin.ignore(100, '\n');

        cout << "\n" << "Choice: ";
        cin >> this->choice;
    }

    cin.ignore(100, '\n');
    cout << "\n";

    switch (choice)
    {
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
            break;
        case 5: //CHARACTER SHEET
            characters[activeCharacter].printStats();
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
}

void Game::saveCharacters()
{
    ofstream outFile(fileName);
    if (outFile.is_open())
    {
        for (size_t i = 0; i < characters.size(); i++)
        {
            outFile << characters[i].getAsString() << "\n";
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

            Character temp(name, distanceTravelled, gold, level,
                    exp, strength, vitality, dexterity,
                    intelligence, hp, stamina, statPoints,
                    skillPoints);

            this->characters.push_back(Character(temp));
            cout << "Character " << name << " loaded successfully!\n";
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