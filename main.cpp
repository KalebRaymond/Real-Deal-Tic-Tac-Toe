#include <iostream>
#include "TTT_Game.h"


int main()
{

    Opponent opp = Opponent(25000, 0);

    for(int i = 0; i < opp.play_history.size(); ++i)
    {
        std::cout << opp.play_history[i].score << "\n";
        opp.play_history[i].printBoard();
    }

    for(int i = 0; i < 5; ++i)
        opp.playVsUser();

}
