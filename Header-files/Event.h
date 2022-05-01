#pragma once

#include <stdlib.h>
#include "Puzzle.h"
#include "Character.h"

class Event
{
public:
    Event();
    virtual ~Event();
    void generateEvent(Character &character);
//    events
    void enemyEncounter (Character &character);
    void puzzleEncounter (Character &character);


private:
    int nrOfEvents;

};