#include <iostream>
#include "TTT_Game.h"

int main()
{
    std::vector<TTT_Game> game_history;
    //TTT_Game t;
    for(int i = 0; i < 100; ++i)
    {
        game_history.push_back(TTT_Game());
    }

    for(TTT_Game t : game_history)
    {
        std::cout << t.checkWin() << "\n";

    }
}
