#pragma once

#include <stdlib.h>
#include "Puzzle.h"
#include "Character.h"

class Event
{
public:
    Event();
    virtual ~Event();
    void generateEvent(Character &character, dArr<Enemy>& enemies);
//    events
    void enemyEncounter (Character &character, dArr<Enemy>& enemies);
    void puzzleEncounter (Character &character);


private:
    int nrOfEvents;

};