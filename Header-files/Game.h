#pragma once

#include "Functions.h"
#include "Event.h"
#include <ctime>
#include <vector>
#include <sstream>

class Game
        {
    public:
            Game();
            virtual ~Game();

//operators

//functions
            void initGame();
            void mainMenu();
            void createNewCharacter();
            void levelUpCharacter();
            void saveCharacters();
            void loadCharacters();
            void selectCharacter();
            void Travel();
            void rest();


//Accessors
            inline bool getPlaying() const { return this->playing; }

//Modifiers




    private:
            int choice;
            bool playing;

//Character related
            int activeCharacter;
            vector<Character> characters;
            string fileName;

//    Enemies related
            dArr<Enemy> enemies;

        };