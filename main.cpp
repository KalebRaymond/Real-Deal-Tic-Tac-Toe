#include <iostream>
#include "TTT_Game.h"


int main()
{

    Opponent opp = Opponent(100000);

    for(int i = 0; i < opp.play_history.size(); ++i)
    {
        std::cout << opp.play_history[i].score << "\n";
        opp.play_history[i].printBoard();
    }

    opp.playVsUser();
}
