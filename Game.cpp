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
    system("CLS");

    if (this->characters[activeCharacter].getExp() >=
        this->characters[activeCharacter].getExpNext())
    {
        cout << "LEVEL UP AVAILABLE! \n\n";
    }
    cout << " -=MAIN MENU=- " << endl << endl;

    cout << "0: Quit" << endl;
    cout << "1: Travel" << endl;
    cout << "2: Shop" << endl;
    cout << "3: Level up" << endl;
    cout << "4: Rest" << endl;
    cout << "5: Character sheet" << endl;
    cout << "6: Create a new character" << endl;
    cout << "7: Save characters" << endl;
    cout << "8: Load characters" << endl;
    cout << endl;

    cout << endl << "Choice: ";
    cin >> choice;

    while (cin.fail())
    {
        cout << "Faulty input!" << "\n";
        cin.clear();
        cin.ignore(100, '\n');

        cout << endl << "Choice: ";
        cin >> choice;
    }

    cin.ignore(100, '\n');
    cout << endl;

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
            this->characters[activeCharacter].levelUp();
            break;
        case 4: //REST
            break;
        case 5: //CHARACETER SHEET
            characters[activeCharacter].printStats();
            break;
        case 6: //CREATE A NEW CHARACTER
            cin.ignore();
            createNewCharacter();
            saveCharacters();
            break;
        case 7: //SAVE CHARACTERS
            saveCharacters();
            break;
        case 8: //LOAD CHARACTERS
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

    characters.push_back(Character());
    activeCharacter = characters.size() -1;
    characters[activeCharacter].initialize(name);
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

void Game::Travel()
{
    this->characters[activeCharacter].travel();
    Event ev;
    ev.generateEvent(this->characters[activeCharacter]);

}