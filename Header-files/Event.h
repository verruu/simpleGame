#pragma once

#include "STLINCLUDE.h"

#include "Puzzle.h"
#include "Character.h"
#include "Enemy.h"

class Event
{
public:
    Event();
    virtual ~Event();
    void generateEvent(Character &character, dArr<Enemy>& enemies);
//    events
    void enemyEncounter (Character &character, dArr<Enemy>& enemies);
    void puzzleEncounter (Character &character);
    void shopEncounter (Character &character);

    //statics
    static int nrOfEvents;

private:

};