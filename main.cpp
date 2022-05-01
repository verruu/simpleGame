#include "Header-files/Game.h"

int main()
{
    srand(time(NULL));

    int level = 1;
    int i = static_cast<int>
            ((50/3)*((pow(level,3)-
            6*pow(level,2))+
            17*level-12));

    cout << i << endl;

    Game game;
    game.initGame();

    while (game.getPlaying())
    {
        game.mainMenu();
    }

    return 0;
}
